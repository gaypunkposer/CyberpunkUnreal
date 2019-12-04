// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MovementBase.generated.h"

class UAdvancedPawnMovement;
class UMovementAbility;
class AMovementPawn;

USTRUCT(BlueprintType)
struct CYBERPUNKUNREAL_API FMoveState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		float DeltaTime;

	UPROPERTY(BlueprintReadOnly)
		bool CrouchSlide;

	UPROPERTY(BlueprintReadOnly)
		bool Sprint;

	UPROPERTY(BlueprintReadOnly)
		bool Jump;

	UPROPERTY(BlueprintReadOnly)
		bool Grounded;

	UPROPERTY(BlueprintReadOnly)
		FVector DirectionalInput;

	UPROPERTY(BlueprintReadOnly)
		FVector Velocity;

	UPROPERTY(BlueprintReadOnly)
		FVector LateralVelocity;

	UPROPERTY(BlueprintReadOnly)
		FVector GroundNormal;

	UPROPERTY(BlueprintReadOnly)
		UMovementAbility* Ability;
};


class CYBERPUNKUNREAL_API MovementBase
{
public:

};
