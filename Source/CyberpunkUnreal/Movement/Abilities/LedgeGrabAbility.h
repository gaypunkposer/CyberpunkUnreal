// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementAbility.h"
#include "Movement/MovementBase.h"
#include "LedgeGrabAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API ULedgeGrabAbility : public UMovementAbility
{
	GENERATED_BODY()

	FVector LedgeNormal;
	bool PullingUp;
	bool TopOfWall;
	bool PreviouslyJumping;

	bool FrontCheck();
	bool TopCheck();
	bool MainCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float GrabHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float PullUpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float LaunchOffForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float JumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShiftSpeed;
public:
	ULedgeGrabAbility();
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	FVector GetVelocity(FMoveState current, FMoveState previous) override;
};