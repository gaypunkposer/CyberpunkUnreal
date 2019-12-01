// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementAbility.generated.h"

USTRUCT()
struct CYBERPUNKUNREAL_API FMoveState
{
	GENERATED_BODY()

		float DeltaTime;
		bool CrouchSlide;
		bool Sprint;
		bool Jump;
		bool Grounded;
		FVector DirectionalInput;
		FVector Velocity;
		FVector LateralVelocity;
		FVector GroundNormal;
		UMovementAbility* Ability;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERPUNKUNREAL_API UMovementAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementAbility();

	inline friend bool operator< (const UMovementAbility& lhs, const UMovementAbility& rhs) { return lhs.Priority > rhs.Priority; }

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Priority = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Speed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Stickiness = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* MoveSound;


public:	
	inline int GetPriority() { return Priority; }
	virtual bool ShouldUseThisAbility(FMoveState current, FMoveState previous);
	virtual FVector GetVelocity(FMoveState current, FMoveState previous);
	virtual FVector GetCameraPosition(FMoveState current);
	virtual float GetCameraTilt(FMoveState current);
	virtual float GetCameraLook(FMoveState current);
	virtual USoundBase* UpdateAudio();

	/* 
	 * Need to determine the return type of these
	 *
	 * virtual void UpdateCollider();
	 * virtual void UpdateViewmodel();
	 */
		
};
