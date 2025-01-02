// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ApplyEffectsFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Abilities/GameplayAbility_Base.h"
#include "Gameplay/Effects/InstantDamageEffect.h"


void UApplyEffectsFunctionLibrary::ApplyInstantDamageToTarget(UAbilitySystemComponent* TargetAsc, const UGameplayAbility_Base* CurrentAbility, const float Amount)
{
	if (Amount <= 0) return;
	
	const FGameplayEffectSpecHandle SpecHandle = CurrentAbility->MakeOutgoingGameplayEffectSpec(UInstantDamageEffect::StaticClass());
	// SpecHandle.Data.Get()->SetByCallerTagMagnitudes.Add(GTag_SetByCaller_InstantDamage, -Amount);
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(GTag_SetByCaller_InstantDamage, -Amount);

	CurrentAbility->GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAsc);
}
