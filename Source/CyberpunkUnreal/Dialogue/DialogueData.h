// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

USTRUCT(BlueprintType)
struct CYBERPUNKUNREAL_API FDialogueData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, int32> Integers;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, float> Floats;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, FName> Names;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSet<FName> TrueBools;
};
