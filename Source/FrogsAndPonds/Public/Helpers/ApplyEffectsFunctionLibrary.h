// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ApplyEffectsFunctionLibrary.generated.h"

class UGameplayEffect;
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
	static void ApplyDamagePredictionToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, const float Amount);
	
	UFUNCTION(BlueprintCallable)
	static void ApplyPredictedDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, const float Amount);
	
	UFUNCTION(BlueprintCallable)
	static void ApplyUnpredictedDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, const float Amount);

	UFUNCTION(BlueprintCallable)
	static void ApplyEffectToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, TSubclassOf<UGameplayEffect> EffectClass, const float Duration, const float Amount);
};
