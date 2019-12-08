
#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementBase.h"
#include "GameFramework/PawnMovementComponent.h"

#include "AdvancedPawnMovement.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERPUNKUNREAL_API UAdvancedPawnMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

	FCollisionShape GroundCheckShape;
	UCapsuleComponent* PlayerCapsule;
	USkeletalMeshComponent* Viewmodel;
	AMovementPawn* Parent;

	void UpdateCamera(UMovementAbility* Ability, float DeltaTime);
public:
	UAdvancedPawnMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CameraRotTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FMoveState CurrentMoveState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FMoveState PreviousMoveState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	TArray<UMovementAbility*> Abilities;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	void RefreshComponents();
	FMoveState UpdateMoveState(float DeltaTime);
};
