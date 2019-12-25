// Fill out your copyright notice in the Description page of Project Settings.


#include "LedgeGrabAbility.h"
#include "Movement/Abilities/AirAbility.h"
#include "Movement/Abilities/JumpAbility.h"

ULedgeGrabAbility::ULedgeGrabAbility()
{
	Priority = 1;
}

bool ULedgeGrabAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	if (PreviouslyJumping)
	{
		PreviouslyJumping = false;
		return false;
	}

	if (PullingUp)
	{
		if (!FrontCheck())
		{
			TopOfWall = true;
			PullingUp = false;
		}

		else if (!TopCheck())
		{
			PullingUp = false;
			return false;
		}

		return true;
	}

	if ((previous.Ability->IsA<UJumpAbility>() || previous.Ability->IsA<UAirAbility>()) && MainCheck())
	{
		if (current.JumpHeld) {
			PullingUp = true;
			return true;
		}
	}

	LedgeNormal = FVector::ZeroVector;
	PullingUp = false;
	TopOfWall = false;
	return false;
}

FVector ULedgeGrabAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	if (!PullingUp) 
	{
		return LedgeNormal * Speed + FVector::UpVector * 250.f;
	}

	FVector targetVelocity = -current.Velocity;

	if (TopOfWall)
	{
		FVector right = FVector::CrossProduct(FVector::UpVector, LedgeNormal);
		targetVelocity += right * current.DirectionalInput.Y * ShiftSpeed * FVector::DotProduct(right, GetOwner()->GetActorRightVector());
	}
	else	
	{
		targetVelocity += FVector::UpVector * PullUpSpeed;
	}

	return targetVelocity;
}

bool ULedgeGrabAbility::FrontCheck() 
{
	FHitResult hitResult;
	FCollisionQueryParams params = FCollisionQueryParams();
	params.AddIgnoredActor(GetOwner());

	FCollisionShape shape = FCollisionShape::MakeBox(FVector(25.f, 50.f, 25.f));

	bool result = GetWorld()->SweepSingleByChannel(hitResult,
		GetOwner()->GetActorLocation() + FVector::UpVector * 25.f,
		GetOwner()->GetActorLocation() + FVector::UpVector * 25.f + GetOwner()->GetActorForwardVector() * 33.f,
		GetOwner()->GetActorQuat(), ECC_WorldStatic, shape, params);
	//            bool result = Physics.BoxCast(transform.position + Vector3.up * 0.25f, new Vector3(0.25f, 0.5f, 0.25f), direction, out info, Quaternion.identity, 0.33f, 1);
	LedgeNormal = hitResult.Normal;
	return result && GetOwner()->GetActorForwardVector().CosineAngle2D(-hitResult.Normal) < 45.f;
}

bool ULedgeGrabAbility::TopCheck()
{
	FHitResult result;
	FCollisionQueryParams params = FCollisionQueryParams();
	params.AddIgnoredActor(GetOwner());

	return !GetWorld()->LineTraceSingleByChannel(result,
		GetOwner()->GetActorLocation() + FVector::UpVector * GrabHeight,
		GetOwner()->GetActorLocation() + FVector::UpVector * GrabHeight + GetOwner()->GetActorForwardVector() * 150.f,
		ECC_WorldStatic, params);
}

bool ULedgeGrabAbility::MainCheck()
{
	return FrontCheck() && TopCheck();
}