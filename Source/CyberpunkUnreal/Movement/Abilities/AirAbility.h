// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "AirAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API UAirAbility : public UMovementAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAirAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AirResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Weight;

protected:


public:
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	FVector GetVelocity(FMoveState current, FMoveState previous) override;
};
