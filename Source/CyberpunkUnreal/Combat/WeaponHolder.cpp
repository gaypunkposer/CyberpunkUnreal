// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHolder.h"

// Sets default values
AWeaponHolder::AWeaponHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

