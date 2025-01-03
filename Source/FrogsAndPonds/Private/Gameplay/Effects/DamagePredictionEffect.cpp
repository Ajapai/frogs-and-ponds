// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Effects/DamagePredictionEffect.h"

#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Attributes/DefensiveAttributeSet.h"

UDamagePredictionEffect::UDamagePredictionEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo GameplayModifierInfo;
	GameplayModifierInfo.Attribute = UDefensiveAttributeSet::GetPredictedHealthAttribute();
	GameplayModifierInfo.ModifierOp = EGameplayModOp::AddBase;

	FSetByCallerFloat SetByCallerMagnitude;
	SetByCallerMagnitude.DataTag = GTag_SetByCaller_Amount;
	GameplayModifierInfo.ModifierMagnitude = SetByCallerMagnitude;
	
	Modifiers.Add(GameplayModifierInfo);
}
