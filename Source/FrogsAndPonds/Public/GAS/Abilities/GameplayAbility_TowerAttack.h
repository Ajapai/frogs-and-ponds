// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/GameplayAbility_Base.h"
#include "GameplayAbility_TowerAttack.generated.h"

class ATowerBase;
/**
 * 
 */
UCLASS(Abstract)
class FROGSANDPONDS_API UGameplayAbility_TowerAttack : public UGameplayAbility_Base
{
	GENERATED_BODY()


	// Lifecycle
public:
	UGameplayAbility_TowerAttack();
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	
// Virtuals
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	
// UFunctions
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAttack();
	

// Functions
protected:
	void OnAttackReady();
	void OnAttackSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;


// UProperties
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ATowerBase> OwningTower;
	

// Pointers
private:
	FTimerManager* TimerManager;

	
// Variables
private:
	FTimerHandle AttackTimer;
	FTimerDelegate AttackTimerDelegate;
};
