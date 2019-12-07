// Fill out your copyright notice in the Description page of Project Settings.


#include "CrouchAbility.h"

UCrouchAbility::UCrouchAbility()
{
	Priority = 4;
}

bool UCrouchAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous)
{
	return (current.CrouchSlide || CrouchTouchingRoof()) && current.Grounded;
}

void UCrouchAbility::UpdateCollider(UCapsuleComponent* Capsule)
{
	Capsule->SetCapsuleHalfHeight(48.f);
}

bool UCrouchAbility::CrouchTouchingRoof()
{
	FHitResult outHit;
	FCollisionShape shape = FCollisionShape::MakeCapsule(55.f, 48.f);
	FCollisionQueryParams collParam = FCollisionQueryParams();
	collParam.AddIgnoredActor(GetOwner());

	return GetWorld()->SweepSingleByChannel(outHit, GetOwner()->GetActorLocation(),
		GetOwner()->GetActorLocation() + GetOwner()->GetActorUpVector() * 48.f,
		GetOwner()->GetActorQuat(), ECollisionChannel::ECC_WorldStatic, shape, collParam);
}