// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/Attributes/AttributeSetBase.h"
#include "OffensiveAttributeSet.generated.h"

USTRUCT()
struct FOffensiveAttributeStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="OffensiveAttributes")
	float AttackPower = 10;
	UPROPERTY(EditDefaultsOnly, Category="OffensiveAttributes")
	float AttackSpeed = 1;
	UPROPERTY(EditDefaultsOnly, Category="OffensiveAttributes")
	float AttackRange = 400;
};

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UOffensiveAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	
	// Virtuals
private:
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UOffensiveAttributeSet, AttackPower);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UOffensiveAttributeSet, AttackSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS(UOffensiveAttributeSet, AttackRange);	
};
