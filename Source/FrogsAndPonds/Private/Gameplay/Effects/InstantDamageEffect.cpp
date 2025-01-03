// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Effects/InstantDamageEffect.h"

#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Attributes/DefensiveAttributeSet.h"

UInstantDamageEffect::UInstantDamageEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo GameplayModifierInfo;
	GameplayModifierInfo.Attribute = UDefensiveAttributeSet::GetHealthAttribute();
	GameplayModifierInfo.ModifierOp = EGameplayModOp::AddBase;

	FSetByCallerFloat SetByCallerMagnitude;
	SetByCallerMagnitude.DataTag = GTag_SetByCaller_InstantDamage;
	GameplayModifierInfo.ModifierMagnitude = SetByCallerMagnitude;
	
	Modifiers.Add(GameplayModifierInfo);
}
