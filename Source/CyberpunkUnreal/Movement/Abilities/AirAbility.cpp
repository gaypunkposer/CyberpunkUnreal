// Fill out your copyright notice in the Description page of Project Settings.


#include "AirAbility.h"

UAirAbility::UAirAbility() 
{
	Priority = 0;
}

bool UAirAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous) 
{
	return true;
}

FVector UAirAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	FVector targetVelocity = current.DirectionalInput * Speed;

	if (previous.Grounded && previous.Ability != nullptr)
	{
		targetVelocity.Z += previous.Ability->Stickiness;
	}

	targetVelocity -= current.LateralVelocity * AirResistance;
	targetVelocity /= Weight / current.DeltaTime;
	targetVelocity.Z -= Gravity * current.DeltaTime;

	return targetVelocity;
}