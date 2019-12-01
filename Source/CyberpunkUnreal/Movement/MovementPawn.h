// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovementAbility.h"
#include "MovementPawn.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API AMovementPawn : public APawn
{
	GENERATED_BODY()

	TArray<UMovementAbility*> Abilities;

public:
	// Sets default values for this pawn's properties
	AMovementPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* BodyMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FMoveState CurrentMoveState;
	FMoveState PreviousMoveState;

	FVector Velocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RefreshMovementComponents();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
