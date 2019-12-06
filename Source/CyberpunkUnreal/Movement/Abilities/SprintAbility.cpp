// Fill out your copyright notice in the Description page of Project Settings.

#include "SprintAbility.h"

USprintAbility::USprintAbility()
{
	Priority = 3;
}

bool USprintAbility::ShouldUseThisAbility(FMoveState current, FMoveState previous) 
{
	return current.Grounded && current.Sprint;
}