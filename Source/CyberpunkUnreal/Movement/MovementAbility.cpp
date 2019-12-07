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
	FVector vel = -current.Velocity;
	vel += dir * Speed;
	vel -= GetOwner()->GetActorUpVector() * Stickiness;

	return vel;
}

void UMovementAbility::UpdateCollider(UCapsuleComponent* Capsule) 
{
	Capsule->SetCapsuleHalfHeight(96.f);
}

FVector UMovementAbility::GetCameraPosition(FMoveState current)
{
	return FVector::UpVector;
}

float UMovementAbility::GetCameraTilt()
{
	return 0.0f;
}

float UMovementAbility::GetCameraLook()
{
	return GetOwner()->GetActorForwardVector().Z;
}

USoundBase* UMovementAbility::UpdateAudio()
{
	return MoveSound;
}