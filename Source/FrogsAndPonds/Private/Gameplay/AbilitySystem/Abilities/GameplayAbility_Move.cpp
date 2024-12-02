// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilitySystem/Abilities/GameplayAbility_Move.h"

#include "Core/GameplayTagsDeclaration.h"

UGameplayAbility_Move::UGameplayAbility_Move()
{
	SetAssetTags(FGameplayTagContainer(GTag_Ability_Move));
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
