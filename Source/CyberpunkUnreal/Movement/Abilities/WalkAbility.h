// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "Components/ActorComponent.h"

#include "WalkAbility.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERPUNKUNREAL_API UWalkAbility : public UMovementAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWalkAbility();

protected:
	

public:	
	virtual bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
};
