// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AttributeSetBase.h"
#include "TowerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UTowerAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	
// Lifecycle
public:
	UTowerAttributeSet();

	
// Virtuals
private:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UTowerAttributeSet, AttackPower);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UTowerAttributeSet, AttackSpeed);
};
