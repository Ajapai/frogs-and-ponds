// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/TowerAttributeSet.h"

UTowerAttributeSet::UTowerAttributeSet():
AttackPower(1),
AttackSpeed(1)
{
}

void UTowerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UTowerAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributeOnChange(Attribute, NewValue);
}
