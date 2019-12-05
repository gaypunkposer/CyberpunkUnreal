// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPawnMovement.h"
#include "Movement/MovementPawn.h"
#include "Movement/MovementAbility.h"

UAdvancedPawnMovement::UAdvancedPawnMovement()
{
	GroundCheckShape = FCollisionShape::MakeCapsule(55.f, 96.f);
}

void UAdvancedPawnMovement::BeginPlay()
{
	Super::BeginPlay();
	RefreshComponents();
	PreviousMoveState = UpdateMoveState(0.f);
}

void UAdvancedPawnMovement::RefreshComponents()
{
	GetOwner()->GetComponents<UMovementAbility>(Abilities);
	Abilities.Sort();
}

void UAdvancedPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	PreviousMoveState = CurrentMoveState;
	CurrentMoveState = UpdateMoveState(DeltaTime);
	UMovementAbility* ability = nullptr;

	for (UMovementAbility* poss : Abilities)
	{
		if (poss->ShouldUseThisAbility(CurrentMoveState, PreviousMoveState))
		{
			ability = poss;
			break;
		}
	}

	if (ability == nullptr)
	{
		return;
	}

	CurrentMoveState.Ability = ability;

	DrawDebugCapsule(GetWorld(), GetActorLocation(), GroundCheckShape.GetCapsuleHalfHeight(), GroundCheckShape.GetCapsuleRadius(), GetOwner()->GetActorQuat(), FColor::Purple, false, 1.f);
	Velocity += ability->GetVelocity(CurrentMoveState, PreviousMoveState);

	if (!Velocity.IsNearlyZero())
	{
		FHitResult hit;
		SafeMoveUpdatedComponent(Velocity * DeltaTime, UpdatedComponent->GetComponentRotation(), true, hit);

		if (hit.IsValidBlockingHit())
		{
			SlideAlongSurface(Velocity * DeltaTime, 1.f - hit.Time, hit.Normal, hit);
		}
	}

	UpdateComponentVelocity();
}

FMoveState UAdvancedPawnMovement::UpdateMoveState(float DeltaTime)
{
	FMoveState state = FMoveState();

	state.DeltaTime = DeltaTime;

	AMovementPawn* parent = Cast<AMovementPawn>(GetOwner());

	state.CrouchSlide = parent->GetCrouchPressed();
	state.Jump = parent->ConsumeJump();
	state.Sprint = parent->GetSprintPressed();
	state.DirectionalInput = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	state.Velocity = Velocity;
	state.LateralVelocity = FVector(Velocity.X, Velocity.Y, 0);

	FHitResult outHit;
	FCollisionQueryParams collParam = FCollisionQueryParams();
	collParam.AddIgnoredActor(GetOwner());
	state.Grounded = GetWorld()->SweepSingleByChannel(outHit, GetOwner()->GetActorLocation(),
		GetOwner()->GetActorLocation() - GetOwner()->GetActorUpVector(),
		GetOwner()->GetActorQuat(), ECollisionChannel::ECC_WorldStatic, GroundCheckShape, collParam);
	state.GroundNormal = outHit.Normal;

	return state;
}