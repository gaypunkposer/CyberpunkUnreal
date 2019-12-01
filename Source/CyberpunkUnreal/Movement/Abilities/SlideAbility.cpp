// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideAbility.h"

USlideAbility::USlideAbility() 
{
	Priority = 5;
}

bool USlideAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	BoostTime = (BoostTime > 0) ? BoostTime - current.DeltaTime : 0;
	PreviousZ = GetOwner()->GetActorTransform().GetLocation().Z;

	if (current.Grounded && current.CrouchSlide) {
		if (current.LateralVelocity.Size() > SlideStartSpeed) 
		{
			if (!previous.Grounded) 
			{
				PreviouslySliding = true;
			}
			return true;
		}
		return false;
	}
	else
	{
		PreviouslySliding = false;
		return false;
	}
}

FVector USlideAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	FVector targetVelocity = HorizontalSpeed * current.DirectionalInput.Y * GetOwner()->GetActorRightVector();

	if (!PreviouslySliding && BoostTime <= 0)
	{
		FVector addVelocity = FVector::VectorPlaneProject(current.Velocity, current.GroundNormal);
		addVelocity.Z -= current.Velocity.Z;
		addVelocity *= Speed;
		addVelocity += targetVelocity;

		PreviouslySliding = true;
		BoostTime = BoostCooldownTime;
		return addVelocity;
	}

	float zDiff = PreviousZ - GetOwner()->GetActorTransform().GetLocation().Z;

	targetVelocity -= current.Velocity * Friction * current.DeltaTime;
	targetVelocity.Z = -current.Velocity.Z;
	targetVelocity.Z -= Stickiness;
	targetVelocity += current.Velocity.GetSafeNormal() * ZBoost * zDiff;

	PreviouslySliding = true;
	return targetVelocity;
}