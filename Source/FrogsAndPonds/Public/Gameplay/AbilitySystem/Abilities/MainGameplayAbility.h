// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MainGameplayAbility.generated.h"


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
UCLASS()
class FROGSANDPONDS_API UMainGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


	// Constructor
public:
	UMainGameplayAbility();

	
	// UProperties
private:
	UPROPERTY(EditAnywhere, Category="Custom")
	EAbilityInputID AbilityInputID;


	// Member Functions
public:
	EAbilityInputID GetAbilityInputId() const;
};
