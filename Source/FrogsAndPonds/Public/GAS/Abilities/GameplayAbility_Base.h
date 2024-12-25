// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"


UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel
};


/**
 * 
 */
UCLASS(Abstract)
class FROGSANDPONDS_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()


// Lifecycle
public:
	UGameplayAbility_Base();

	
// Functions
public:
	EAbilityInputID GetAbilityInputId() const;

	
// UProperties
private:
	UPROPERTY(EditAnywhere, Category="Custom")
	EAbilityInputID AbilityInputID;
};
