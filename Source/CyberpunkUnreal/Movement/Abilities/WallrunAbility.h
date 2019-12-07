// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "Kismet/KismetMathLibrary.h"

#include "WallrunAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API UWallrunAbility : public UMovementAbility
{
	GENERATED_BODY()

	bool PreviouslyEscaping;
	bool Leave;
	float EnterVelocity;
	float EnterDegree;
	FVector WallNormal;

	bool PreCheck(FMoveState current);
	bool MainCheck(FMoveState current, FMoveState previous);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MinEnterVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WallEscapeForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WallLeaveInfluence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float EscapeJumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WallGravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float Friction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WallEnterInfluence;
public:

	UWallrunAbility();
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	FVector GetVelocity(FMoveState current, FMoveState previous) override;
	float GetCameraTilt() override;
	float GetCameraLook() override;
};