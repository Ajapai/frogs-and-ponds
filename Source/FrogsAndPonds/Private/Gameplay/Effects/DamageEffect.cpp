// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Effects/DamageEffect.h"

#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Attributes/DefensiveAttributeSet.h"

UDamageEffect::UDamageEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo GameplayModifierInfo;
	GameplayModifierInfo.Attribute = UDefensiveAttributeSet::GetHealthAttribute();
	GameplayModifierInfo.ModifierOp = EGameplayModOp::AddBase;

	FSetByCallerFloat SetByCallerMagnitude;
	SetByCallerMagnitude.DataTag = GTag_SetByCaller_Amount;
	GameplayModifierInfo.ModifierMagnitude = SetByCallerMagnitude;
	
	Modifiers.Add(GameplayModifierInfo);
}
