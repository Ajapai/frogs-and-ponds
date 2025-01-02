// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/Attributes/AttributeSetBase.h"
#include "DefenderAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UDefenderAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	
// Virtuals
private:
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData Health = 40;
	ATTRIBUTE_ACCESSORS(UDefenderAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MaxHealth = 40;
	ATTRIBUTE_ACCESSORS(UDefenderAttributeSet, MaxHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MoveSpeed = 10;
	ATTRIBUTE_ACCESSORS(UDefenderAttributeSet, MoveSpeed);

};
