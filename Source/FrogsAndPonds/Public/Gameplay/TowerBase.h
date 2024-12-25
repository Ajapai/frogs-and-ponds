// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Helpers/Property.h"
#include "AbilitySystemGlobals.h"
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
	void OnLockedOnEnemyChange(AEnemyBase* PreviousTarget, AEnemyBase* NewTarget);

	
// Accessors
public:
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "Enemy")
	AEnemyBase* GetLockedOnEnemy() const;
	
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "AttackPower")
	float GetAttackPower() const;
	
	UFUNCTION(BlueprintPure)
	UPARAM(DisplayName = "AttackSpeed")
	float GetAttackSpeed() const;
	
	
// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UGameplayAbility_TowerAttack>> AttackAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UGameplayAbility_Base>> LockOnAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UAttributeSetBase>> DefaultAttributes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category="Custom|Component")
	TObjectPtr<USceneComponent> BulletSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<USphereComponent> AttackSphere;

	
// Variables
private:
	TArray<TObjectPtr<AEnemyBase>> EnemiesInRange;
	Property<AEnemyBase*> LockedOnEnemy = Property<AEnemyBase*>([this](auto PreviousTarget, auto NewTarget)
	{
		OnLockedOnEnemyChange(PreviousTarget, NewTarget);
		UAbilitySystemGlobals::Get();
	});

};
