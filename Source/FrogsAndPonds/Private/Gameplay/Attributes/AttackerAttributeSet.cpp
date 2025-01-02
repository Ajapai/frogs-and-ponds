// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Attributes/AttackerAttributeSet.h"

void UAttackerAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributeOnChange(Attribute, NewValue);
}
