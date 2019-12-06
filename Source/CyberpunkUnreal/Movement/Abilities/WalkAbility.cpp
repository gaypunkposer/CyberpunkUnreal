// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkAbility.h"

UWalkAbility::UWalkAbility()
{
	Priority = 2;
}

bool UWalkAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous) 
{
	return current.Grounded;
}