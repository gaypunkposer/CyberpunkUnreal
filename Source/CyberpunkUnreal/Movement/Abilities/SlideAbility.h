// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementBase.h"
#include "Movement/MovementAbility.h"
#include "SlideAbility.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERPUNKUNREAL_API USlideAbility : public UMovementAbility
{
	GENERATED_BODY()

	float BoostTime;
	float PreviousZ;
	bool PreviouslySliding;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float SlideStartSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float HorizontalSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Friction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float BoostCooldownTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ZBoost;
public:	
	USlideAbility();
	bool ShouldUseThisAbility(FMoveState current, FMoveState previous) override;
	void UpdateCollider(UCapsuleComponent* Capsule) override;
	FVector GetVelocity(FMoveState current, FMoveState previous) override;
};
