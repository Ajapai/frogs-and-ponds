// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet():
Health(40.f),
MaxHealth(40.f),
MoveSpeed(3.f),
MaxMoveSpeed(6.f),
Distance(0.f),
MaxDistance(100.f)
{
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UEnemyAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributeOnChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(GetHealth(), 0, GetMaxHealth());
	}
	else if (Attribute == GetMoveSpeedAttribute())
	{
		NewValue = FMath::Clamp(GetMoveSpeed(), 0, GetMaxMoveSpeed());
	}
	else if (Attribute == GetDistanceAttribute())
	{
		NewValue = FMath::Clamp(GetDistance(), 0,  GetMaxDistance());
	}
}
