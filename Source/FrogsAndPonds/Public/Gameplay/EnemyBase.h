// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Attributes/DefensiveAttributeSet.h"
#include "Attributes/OffensiveAttributeSet.h"
#include "EnemyBase.generated.h"

class UCapsuleComponent;
class UAttributeSetBase;
class AEnemyPath;
class USplineComponent;
class UGameplayAbility_Base;


UCLASS(Abstract)
class FROGSANDPONDS_API AEnemyBase : public AActor, public IAbilitySystemInterface 
{
	GENERATED_BODY()

	
// Lifecycle
public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;


// Operators
public:
	bool operator<(const AEnemyBase& Other) const
	{
		return MoveDistance < Other.MoveDistance;
	}

	
// Virtuals
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;


	// UFunctions
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float OldValue, float NewValue);

	
// Functions
private:
	void InitializeAbilities();
	void InitializeAttributes();
	void HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void PredictedHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;
	
	
// Accessors
public:
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintPure)
	float GetMoveSpeed() const;
	UFUNCTION(BlueprintPure)
	float GetMoveDistance() const;
	
	const USceneComponent* GetProjectileTarget();

	
// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TArray<TSubclassOf<UGameplayAbility_Base>> DefaultAbilities;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TObjectPtr<USceneComponent> ProjectileTarget;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Attributes")
	FOffensiveAttributeStruct OffensiveAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom|Attributes")
	FDefensiveAttributeStruct DefensiveAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	
// Variables
private:
	TArray<TSubclassOf<UAttributeSetBase>> DefaultAttributes;
	TWeakObjectPtr<USplineComponent> SplineComponent;
	float MoveDistance = 0;
};
