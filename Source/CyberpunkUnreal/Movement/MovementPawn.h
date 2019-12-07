// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MovementBase.h"
#include "MovementPawn.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API AMovementPawn : public APawn
{
	GENERATED_BODY()

	inline void OnBeginJump() { JumpPressed = true; };
	inline void OnEndJump() { JumpPressed = false; };

	inline void OnBeginCrouch() { CrouchPressed = true; };
	inline void OnEndCrouch() { CrouchPressed = false; };

	inline void OnBeginSprint() { SprintPressed = true; };
	inline void OnEndSprint() { SprintPressed = false; };

	void MoveForward(float Degree);
	void MoveRight(float Degree);
	void Turn(float Degree);
	void LookUp(float Degree);

public:
	// Sets default values for this pawn's properties
	AMovementPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
    class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
    class USkeletalMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int TurnRate = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAdvancedPawnMovement* MovementComponent;

protected:
	virtual void BeginPlay() override;
	
	UInputComponent* Input;
	bool CrouchPressed;
	bool JumpPressed;
	bool SprintPressed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAdvancedPawnMovement* GetAdvancedMovementComponent();

	inline bool GetCrouchPressed() { return CrouchPressed; };
	bool ConsumeJump();
	inline bool GetSprintPressed() { return SprintPressed; };
};