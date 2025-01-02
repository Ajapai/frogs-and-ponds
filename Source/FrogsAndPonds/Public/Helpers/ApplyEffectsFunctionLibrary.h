// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ApplyEffectsFunctionLibrary.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility_Base;
/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API UApplyEffectsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
// UFunctions
public:
	UFUNCTION(BlueprintCallable)
	static void ApplyInstantDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, const float Amount);
};
