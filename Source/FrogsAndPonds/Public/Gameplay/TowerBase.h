// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attributes/OffensiveAttributeSet.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

class UGameplayAbility_TowerAttack;
class AEnemyBase;
class USphereComponent;
class UAttributeSetBase;
class UGameplayAbility_Base;


UCLASS()
class FROGSANDPONDS_API ATowerBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()


// Lifecycle
public:
	ATowerBase();

protected:
	virtual void BeginPlay() override;


// Virtuals
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;


// UFunctions
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
// Functions
private:
	void InitializeAbilities();
	void InitializeAttributes();
	void UpdateAttackRange() const;

	
// Accessors
public:
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "AttackPower")
	float GetAttackPower() const;
	
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "AttackSpeed")
	float GetAttackSpeed() const;
	
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "AttackRange")
	float GetAttackRange() const;

	UFUNCTION(BlueprintPure)
	const USceneComponent* GetBulletSpawnPoint() const;
	
	
// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UGameplayAbility_TowerAttack>> AttackAbilities;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Attributes")
	FOffensiveAttributeStruct OffensiveAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<USceneComponent> BulletSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<USphereComponent> AttackRangeSphere;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<UDecalComponent> AttackRangeDecal;

	
// Variables
public:
	TArray<TSubclassOf<UAttributeSetBase>> DefaultAttributes;
	TArray<TObjectPtr<AEnemyBase>> EnemiesInRange;
};
