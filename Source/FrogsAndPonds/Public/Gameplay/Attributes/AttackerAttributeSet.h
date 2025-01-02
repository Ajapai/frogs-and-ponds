// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/Attributes/AttributeSetBase.h"
#include "AttackerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UAttackerAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	
	// Virtuals
private:
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackPower = 10;
	ATTRIBUTE_ACCESSORS(UAttackerAttributeSet, AttackPower);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackSpeed = 1;
	ATTRIBUTE_ACCESSORS(UAttackerAttributeSet, AttackSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackRange = 400;
	ATTRIBUTE_ACCESSORS(UAttackerAttributeSet, AttackRange);	
};
