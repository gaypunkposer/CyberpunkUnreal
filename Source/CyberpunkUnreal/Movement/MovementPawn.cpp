// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementPawn.h"

// Sets default values
AMovementPawn::AMovementPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FirstPersonCollision"));
	CapsuleCollider->InitCapsuleSize(55.f, 96.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    CameraComponent->SetupAttachment(CapsuleCollider);
    CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeLocation(FVector(0, 0, 100));

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	
}

// Called when the game starts or when spawned
void AMovementPawn::BeginPlay()
{
	Super::BeginPlay();
	RefreshMovementComponents();
}

void AMovementPawn::RefreshMovementComponents() 
{
	GetComponents<UMovementAbility>(Abilities);
	Abilities.Sort();
}

// Called every frame
void AMovementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FMoveState AMovementPawn::GetMoveState(float DeltaTime, FVector GroundNormal)
{
    FMoveState output = FMoveState();
    
    output.
    
    return output;
}
