// Fill out your copyright notice in the Description page of Project Settings.


#include "WallrunAbility.h"
#include "LedgeGrabAbility.h"

UWallrunAbility::UWallrunAbility() 
{
	Priority = 7;
}

bool UWallrunAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	if (PreviouslyEscaping)
	{
		PreviouslyEscaping = false;
		return false;
	}

	if (!PreCheck(current)) return false;

	if (MainCheck(current, previous) && ((previous.Ability != nullptr && previous.Ability->IsA<UWallrunAbility>()) ||
		current.Velocity.Size() > MinEnterVelocity))
	{
		Leave = false;
		
		return !previous.Ability->IsA<ULedgeGrabAbility>();
	}

	if (Leave || current.Jump) return false;

	Leave = true;
	return true;
}

bool UWallrunAbility::PreCheck(FMoveState current)
{
	return !(current.CrouchSlide || current.Grounded);
}

bool UWallrunAbility::MainCheck(FMoveState current, FMoveState previous)
{
	FHitResult result;
	FCollisionQueryParams collParam = FCollisionQueryParams();
	collParam.AddIgnoredActor(GetOwner());
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() - GetOwner()->GetActorRightVector() * 33.f, FColor::Green, false, .1f);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorRightVector() * 33.f, FColor::Red, false, .1f);
	if (GetWorld()->LineTraceSingleByChannel(result, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() - GetOwner()->GetActorRightVector() * 57.5f, ECC_WorldStatic, collParam)
		|| GetWorld()->LineTraceSingleByChannel(result, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorRightVector() * 57.5f, ECC_WorldStatic, collParam))
	{
		WallNormal = result.Normal;
		UE_LOG(LogTemp, Warning, TEXT("Wallrun check succeeded, %s"), *result.Actor->GetName());
		return true;
	}
	else 
	{
			WallNormal = FVector::ZeroVector;

		return false;
	}
}

FVector UWallrunAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	float negateStickDeg = FVector::DotProduct(current.Velocity, -WallNormal);

	FVector targetVelocity = current.LateralVelocity * Speed;
	targetVelocity.Z = -current.Velocity.Z;

	if (current.Jump)
	{
		targetVelocity = WallNormal * Stickiness * WallEscapeForce;
		targetVelocity.Z = EscapeJumpHeight;
		PreviouslyEscaping = true;
	}
	else if (Leave)
	{
		targetVelocity *= WallLeaveInfluence;
		targetVelocity.Z = 0;
		targetVelocity += 1.25f * negateStickDeg * WallNormal;
	}
	else 
	{
		if (!previous.Ability->IsA<UWallrunAbility>())
		{
			EnterVelocity = current.Velocity.Size();
		}

		FVector wallForward = FVector::CrossProduct(FVector::UpVector, WallNormal);
		float wallForwardDeg = FVector::DotProduct(wallForward, targetVelocity);

		targetVelocity -= WallNormal * Stickiness;
		targetVelocity -= current.LateralVelocity * Friction;
		targetVelocity += wallForwardDeg * EnterVelocity * WallEnterInfluence * wallForward;
		targetVelocity += negateStickDeg * wallForwardDeg * wallForward;
		targetVelocity += WallNormal * negateStickDeg / 2;
		targetVelocity.Z -= WallGravity * current.DeltaTime;
	}

	return targetVelocity;
}