// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementPawn.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Movement/AdvancedPawnMovement.h"
#include "UI/DialogueWidget.h"
#include "Actions/PawnAction.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAnimInstance.h"
#include "Movement/MovementAbility.h"
#include "DlgContext.h"
#include "DlgManager.h"

// Sets default values
AMovementPawn::AMovementPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FirstPersonCollision"));
	CapsuleCollider->InitCapsuleSize(55.f, 96.0f);

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	BodyMesh->SetupAttachment(CapsuleCollider);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(BodyMesh, TEXT("face"));

	MovementComponent = CreateDefaultSubobject<UAdvancedPawnMovement>(TEXT("PawnMovement"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMovementPawn::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AMovementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CapsuleCollider->SetPhysicsLinearVelocity(MovementComponent->Velocity);
	UpdateMovementAnimations();
}

void AMovementPawn::UpdateMovementAnimations()
{
	if (!BodyMesh) return;
	UPlayerAnimInstance* anim = Cast<UPlayerAnimInstance>(BodyMesh->GetAnimInstance());

	if (!anim) return;
	anim->MoveState = MovementComponent->CurrentMoveState.Ability->Priority;
	anim->Speed = MovementComponent->CurrentMoveState.LateralVelocity.Size();
}

void AMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMovementPawn::OnBeginJump);
	PlayerInputComponent->BindAction("Jump", IE_Repeat, this, &AMovementPawn::OnEndJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMovementPawn::OnEndJump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMovementPawn::OnBeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMovementPawn::OnEndCrouch);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMovementPawn::OnBeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMovementPawn::OnEndSprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMovementPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMovementPawn::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMovementPawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMovementPawn::LookUp);
}

UAdvancedPawnMovement* AMovementPawn::GetAdvancedMovementComponent()
{
	return MovementComponent;
}

void AMovementPawn::MoveForward(float Degree)
{
	if (MovementComponent && MovementComponent->UpdatedComponent == RootComponent)
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * Degree);
	}
}

void AMovementPawn::MoveRight(float Degree)
{
	if (MovementComponent && MovementComponent->UpdatedComponent == RootComponent)
	{
		MovementComponent->AddInputVector(GetActorRightVector() * Degree);
	}
}

void AMovementPawn::Turn(float Degree) 
{
	AddControllerYawInput(Degree * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMovementPawn::LookUp(float Degree)
{
	AddControllerPitchInput(Degree * TurnRate * GetWorld()->GetDeltaSeconds());
}

bool AMovementPawn::ConsumeJump()
{
	bool retval = JumpPressed;
	JumpPressed = false;
	return retval;
}

bool AMovementPawn::ModifyIntValue_Implementation(const FName& ValueName, bool bDelta, int32 Value)
{
	if (!DialogueData.Integers.Contains(ValueName))
		DialogueData.Integers.Add(ValueName, 0);

	if (bDelta)
		DialogueData.Integers[ValueName] += Value;
	else
		DialogueData.Integers[ValueName] = Value;

	return true;
}

bool AMovementPawn::ModifyFloatValue_Implementation(const FName& ValueName, bool bDelta, float Value)
{
	if (!DialogueData.Floats.Contains(ValueName))
		DialogueData.Floats.Add(ValueName, 0.0f);

	if (bDelta)
		DialogueData.Floats[ValueName] += Value;
	else
		DialogueData.Floats[ValueName] = Value;

	return true;
}

bool AMovementPawn::ModifyBoolValue_Implementation(const FName& ValueName, bool bValue)
{
	if (bValue)
		DialogueData.TrueBools.Add(ValueName);
	else
		DialogueData.TrueBools.Remove(ValueName);

	return true;
}

bool AMovementPawn::ModifyNameValue_Implementation(const FName& ValueName, const FName& NameValue)
{
	if (DialogueData.Names.Contains(ValueName))
		DialogueData.Names[ValueName] = NameValue;
	else
		DialogueData.Names.Add(ValueName, NameValue);

	return true;
}

float AMovementPawn::GetFloatValue_Implementation(const FName& ValueName) const
{
	return DialogueData.Floats.Contains(ValueName) ? DialogueData.Floats[ValueName] : 0.0f;
}

int32 AMovementPawn::GetIntValue_Implementation(const FName& ValueName) const
{
	return DialogueData.Integers.Contains(ValueName) ? DialogueData.Integers[ValueName] : 0;
}

bool AMovementPawn::GetBoolValue_Implementation(const FName& ValueName) const
{
	return DialogueData.TrueBools.Contains(ValueName);
}

FName AMovementPawn::GetNameValue_Implementation(const FName& ValueName) const
{
	return DialogueData.Names.Contains(ValueName) ? DialogueData.Names[ValueName] : NAME_None;
}
