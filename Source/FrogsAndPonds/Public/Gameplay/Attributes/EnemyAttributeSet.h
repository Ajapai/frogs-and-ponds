// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UEnemyAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()


// Lifecycle
public:
	UEnemyAttributeSet();

	
// Virtuals
private:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	
// UProperties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MoveSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MoveDistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MoveDistance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	FGameplayAttributeData MaxMoveDistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxMoveDistance);

};
