// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementBase.h"
#include "Movement/MovementAbility.h"
#include "JumpAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API UJumpAbility : public UMovementAbility
{
	GENERATED_BODY()

	bool PreviouslyJumping;
	int JumpCount;

public:
	// Sets default values for this component's properties
	UJumpAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MaxJumps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float JumpThrust;

protected:


public:
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	FVector GetVelocity(FMoveState current, FMoveState previous) override;
};