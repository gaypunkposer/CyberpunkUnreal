// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementAbility.h"

// Sets default values for this component's properties
UMovementAbility::UMovementAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UMovementAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	return false;
}

FVector UMovementAbility::GetVelocity(FMoveState current, FMoveState previous)
{
	FVector dir = current.DirectionalInput;
	FVector vel = FVector();
	vel += GetOwner()->GetActorForwardVector() * dir.X * Speed;
	vel += GetOwner()->GetActorRightVector() * dir.Y * Speed;
	vel -= GetOwner()->GetActorUpVector() * Stickiness;

	return vel;
}

FVector UMovementAbility::GetCameraPosition(FMoveState current)
{
	return FVector::UpVector;
}

float UMovementAbility::GetCameraTilt(FMoveState current)
{
	return 0.0f;
}

float UMovementAbility::GetCameraLook(FMoveState current)
{
	return 0.0f;
}

USoundBase* UMovementAbility::UpdateAudio()
{
	return MoveSound;
}