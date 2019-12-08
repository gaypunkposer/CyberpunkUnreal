// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "CrouchAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API UCrouchAbility : public UMovementAbility
{
	GENERATED_BODY()

	bool CrouchTouchingRoof();

public:
	UCrouchAbility();
	 
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	void UpdateCollider(UCapsuleComponent* Capsule) override;
	void UpdateViewmodel(USkeletalMeshComponent* Mesh) override;
};