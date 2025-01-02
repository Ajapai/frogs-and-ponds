// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Gameplay/Abilities/GameplayAbility_Base.h"
#include "GameplayAbility_TowerAttack.generated.h"

class AEnemyBase;
class AProjectileBase;
class ATowerBase;

UENUM()
enum class ETargetingMethod: uint8
{
	First,
	Last,
	Random
};

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
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetStruck(UAbilitySystemComponent* TargetAsc);

	
// Functions
protected:
	void OnAttackReady();
	void StartAttack();
	AEnemyBase* GetCurrentTarget() const;
	void OnAttackSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;


// UProperties
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ATowerBase> OwningTower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TSubclassOf<AProjectileBase> ProjectileClass;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	ETargetingMethod TargetingMethod = ETargetingMethod::First;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float BaseDamage = 5;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float AttackPowerCoefficient = 1;

	

// Variables
private:
	FTimerDelegate AttackTimerDelegate;
	FTimerHandle AttackTimer;
	FTimerManager* TimerManager;
};
