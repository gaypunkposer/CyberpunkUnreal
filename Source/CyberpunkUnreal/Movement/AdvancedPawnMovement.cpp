// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPawnMovement.h"
#include "Movement/MovementPawn.h"
#include "Movement/MovementAbility.h"

UAdvancedPawnMovement::UAdvancedPawnMovement() 
{
	
}

void UAdvancedPawnMovement::BeginPlay() 
{
	Super::BeginPlay();
	RefreshComponents();
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
	UE_LOG(LogTemp, Warning, TEXT("%d abilities"), Abilities.Num());

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
		//UE_LOG(LogTemp, Error, TEXT("Failed to acquire appropriate move state"));
		return;
	}

	CurrentMoveState.Ability = ability;

	FVector desiredVelocity = ability->GetVelocity(CurrentMoveState, PreviousMoveState);

	if (!desiredVelocity.IsNearlyZero()) 
	{
		FHitResult hit;
		SafeMoveUpdatedComponent(desiredVelocity * DeltaTime, UpdatedComponent->GetComponentRotation(), true, hit);

		if (hit.IsValidBlockingHit())
		{
			SlideAlongSurface(desiredVelocity * DeltaTime, 1.f - hit.Time, hit.Normal, hit);
		}
	}
}

FMoveState UAdvancedPawnMovement::UpdateMoveState(float DeltaTime)
{
	FMoveState state = FMoveState();

	state.DeltaTime = DeltaTime;

	AMovementPawn* parent = Cast<AMovementPawn>(GetOwner());

	state.CrouchSlide = parent->GetCrouchPressed();
	state.Jump = parent->GetJumpPressed();
	state.Sprint = parent->GetSprintPressed();
	state.DirectionalInput = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	
	state.Velocity = Velocity;
	state.LateralVelocity = FVector(Velocity.X, Velocity.Y, 0);

	//TODO: Do ground check
	state.Grounded = true;
	state.GroundNormal = FVector::UpVector;

	return state;
}