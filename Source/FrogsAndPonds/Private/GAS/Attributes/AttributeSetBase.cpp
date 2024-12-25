// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/AttributeSetBase.h"

void UAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttributeOnChange(Attribute, NewValue);
}

void UAttributeSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttributeOnChange(Attribute, NewValue);
}

void UAttributeSetBase::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
}
