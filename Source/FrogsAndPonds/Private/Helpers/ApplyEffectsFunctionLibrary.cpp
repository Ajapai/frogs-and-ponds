// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ApplyEffectsFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Abilities/GameplayAbility_Base.h"
#include "Gameplay/Effects/DamageEffect.h"
#include "Gameplay/Effects/DamagePredictionEffect.h"



void UApplyEffectsFunctionLibrary::ApplyDamagePredictionToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility,
	const float Amount)
{
	if (Amount <= 0) return;
	
	const FGameplayEffectSpecHandle SpecHandle = CurrentAbility->MakeOutgoingGameplayEffectSpec(UDamagePredictionEffect::StaticClass());
	SpecHandle.Data.Get()->SetByCallerTagMagnitudes[GTag_SetByCaller_Amount] = -Amount;
	if (SpecHandle.Data.Get()->SetByCallerTagMagnitudes.Contains(GTag_SetByCaller_Duration)) GEngine->AddOnScreenDebugMessage(
		-1, 5, FColor::Green, "HasDuration", true, {1, 1});

	CurrentAbility->GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAsc);
}

void UApplyEffectsFunctionLibrary::ApplyPredictedDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility,
                                                                const float Amount)
{
	if (Amount <= 0) return;
	TSubclassOf<UGameplayEffect> a = UDamageEffect::StaticClass();
	
	const FGameplayEffectSpecHandle SpecHandle = CurrentAbility->MakeOutgoingGameplayEffectSpec(UDamageEffect::StaticClass());
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(GTag_SetByCaller_Amount, -Amount);


	CurrentAbility->GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAsc);
}

void UApplyEffectsFunctionLibrary::ApplyUnpredictedDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility,
	const float Amount)
{
	ApplyDamagePredictionToTarget(TargetAsc, CurrentAbility, Amount);
	ApplyPredictedDamageToTarget(TargetAsc, CurrentAbility, Amount);
}

void UApplyEffectsFunctionLibrary::ApplyEffectToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility,
	TSubclassOf<UGameplayEffect> EffectClass, const float Duration, const float Amount)
{
	if (Amount <= 0) return;
	
	const FGameplayEffectSpecHandle SpecHandle = CurrentAbility->MakeOutgoingGameplayEffectSpec(EffectClass);
	SpecHandle.Data.Get()->SetByCallerTagMagnitudes[GTag_SetByCaller_Duration] = Duration;
	SpecHandle.Data.Get()->SetByCallerTagMagnitudes[GTag_SetByCaller_Amount] = Amount;

	CurrentAbility->GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAsc);
}
