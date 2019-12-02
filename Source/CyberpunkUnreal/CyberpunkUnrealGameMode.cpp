// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CyberpunkUnrealGameMode.h"
#include "CyberpunkUnrealHUD.h"
#include "CyberpunkUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACyberpunkUnrealGameMode::ACyberpunkUnrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACyberpunkUnrealHUD::StaticClass();
}
