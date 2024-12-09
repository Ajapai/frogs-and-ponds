// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilitySystem/Abilities/GameplayAbility_Base.h"

UGameplayAbility_Base::UGameplayAbility_Base()
{
	AbilityInputID = EAbilityInputID::None;
}

EAbilityInputID UGameplayAbility_Base::GetAbilityInputId() const
{
	return AbilityInputID;
}
