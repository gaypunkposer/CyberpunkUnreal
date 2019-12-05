// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"
#include "Movement/Abilities/WallrunAbility.h"

UJumpAbility::UJumpAbility()
{
	Priority = 6;
}

bool UJumpAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	if (current.Grounded || previous.Ability->IsA<UWallrunAbility>())
	{
		JumpCount = 0;
	}

	if (JumpCount < MaxJumps && !PreviouslyJumping) return current.Jump;

	PreviouslyJumping = false;
	return false;
}

FVector UJumpAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	FVector targetVelocity = current.DirectionalInput;
	targetVelocity *= JumpThrust;
	targetVelocity.Z = Speed + previous.Ability->Stickiness;

	JumpCount++;
	PreviouslyJumping = true;
	return targetVelocity;
}