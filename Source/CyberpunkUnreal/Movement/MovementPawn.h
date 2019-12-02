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

    

public:
	// Sets default values for this pawn's properties
	AMovementPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
    class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
    class USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    FMoveState CurrentMoveState;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    FMoveState PreviousMoveState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    FVector Velocity;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    TArray<UMovementAbility*> Abilities;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RefreshMovementComponents();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    UFUNCTION(BlueprintPure)
    FMoveState GetMoveState(float DeltaTime, FVector GroundNormal);
};
