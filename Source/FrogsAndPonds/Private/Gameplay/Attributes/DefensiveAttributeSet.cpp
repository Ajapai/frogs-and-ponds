// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Attributes/DefensiveAttributeSet.h"

void UDefensiveAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributeOnChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetPredictedHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetHealth());
	}
}
