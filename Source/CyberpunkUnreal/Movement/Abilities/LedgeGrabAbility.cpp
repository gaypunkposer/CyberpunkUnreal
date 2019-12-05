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
		if (!FrontCheck(current, GetOwner()->GetActorForwardVector()))
		{
			TopOfWall = true;
			PullingUp = false;
		}

		else if (false /*Do check*/)
		{

		}

		return current.Jump;
	}

	if ((previous.Ability->IsA<UJumpAbility>() || previous.Ability->IsA<UAirAbility>()) && MainCheck(current))
	{
		PullingUp = true;
		TopOfWall = false;
		return current.Jump;
	}

	LedgeNormal = FVector::ZeroVector;
	return false;
}

FVector ULedgeGrabAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	if (!PullingUp) 
	{
		return LedgeNormal * Speed + FVector::UpVector;
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

bool ULedgeGrabAbility::FrontCheck(FMoveState current, FVector direction) 
{
	return false;
}

bool ULedgeGrabAbility::TopCheck(FMoveState current)
{
	return false;
}

bool ULedgeGrabAbility::MainCheck(FMoveState current)
{
	return FrontCheck(current, GetOwner()->GetActorForwardVector()) && TopCheck(current);
}