// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DlgDialogueParticipant.h"
#include "Dialogue/DialogueData.h"

#include "MovementBase.h"
#include "MovementPawn.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API AMovementPawn : public APawn, public IDlgDialogueParticipant
{
	GENERATED_BODY()

	inline void OnBeginJump() { JumpPressed = true; JumpHeld = true; };
	inline void OnEndJump() { JumpPressed = false; JumpHeld = false; };

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DlgData, meta = (AllowPrivateAccess = "true"))
	FDialogueData DialogueData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DlgData, meta = (AllowPrivateAccess = "true"))
	FName DialogueParticipantName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DlgData, meta = (AllowPrivateAccess = "true"))
	FText DialogueParticipantDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DlgData, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* DialogueParticipantIcon;

protected:
	virtual void BeginPlay() override;

	bool JumpHeld;
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
	inline bool GetJumpHeld() { return JumpHeld; };
	bool ConsumeJump();
	inline bool GetSprintPressed() { return SprintPressed; };

	FName GetParticipantName_Implementation() const override { return DialogueParticipantName; }
	FText GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const override { return DialogueParticipantDisplayName; }
	UTexture2D* GetParticipantIcon_Implementation(FName ActiveSpeaker, FName ActiveSpeakerState) const override { return DialogueParticipantIcon; }

	bool ModifyIntValue_Implementation(const FName& ValueName, bool bDelta, int32 Value) override;
	bool ModifyFloatValue_Implementation(const FName& ValueName, bool bDelta, float Value) override;
	bool ModifyBoolValue_Implementation(const FName& ValueName, bool bValue) override;
	bool ModifyNameValue_Implementation(const FName& ValueName, const FName& NameValue) override;

	float GetFloatValue_Implementation(const FName& ValueName) const override;
	int32 GetIntValue_Implementation(const FName& ValueName) const override;
	bool GetBoolValue_Implementation(const FName& ValueName) const override;
	FName GetNameValue_Implementation(const FName& ValueName) const override;

	bool OnDialogueEvent_Implementation(const FName& EventName) override { return false; }
	bool CheckCondition_Implementation(const FName& ConditionName) const override { return false; }
};