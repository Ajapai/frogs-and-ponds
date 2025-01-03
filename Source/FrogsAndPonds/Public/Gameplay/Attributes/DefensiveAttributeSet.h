// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/Attributes/AttributeSetBase.h"
#include "DefensiveAttributeSet.generated.h"

USTRUCT()
struct FDefensiveAttributeStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 40;
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 10;
};

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UDefensiveAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	
// Virtuals
private:
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData Health = 40;
	ATTRIBUTE_ACCESSORS(UDefensiveAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MaxHealth = 40;
	ATTRIBUTE_ACCESSORS(UDefensiveAttributeSet, MaxHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData PredictedHealth = 40;
	ATTRIBUTE_ACCESSORS(UDefensiveAttributeSet, PredictedHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MoveSpeed = 10;
	ATTRIBUTE_ACCESSORS(UDefensiveAttributeSet, MoveSpeed);

};
