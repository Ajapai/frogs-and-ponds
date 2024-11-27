// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilitySystem/Abilities/MainGameplayAbility.h"

UMainGameplayAbility::UMainGameplayAbility()
{
	AbilityInputID = EAbilityInputID::None;
}

EAbilityInputID UMainGameplayAbility::GetAbilityInputId() const
{
	return AbilityInputID;
}
