// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilitySystem/Abilities/BaseGameplayAbility.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	AbilityInputID = EAbilityInputID::None;
}

EAbilityInputID UBaseGameplayAbility::GetAbilityInputId() const
{
	return AbilityInputID;
}
