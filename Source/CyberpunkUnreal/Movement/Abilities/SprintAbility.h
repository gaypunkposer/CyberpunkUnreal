// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "SprintAbility.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERPUNKUNREAL_API USprintAbility : public UMovementAbility
{
	GENERATED_BODY()
	
public:
	USprintAbility();
    virtual bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
};
