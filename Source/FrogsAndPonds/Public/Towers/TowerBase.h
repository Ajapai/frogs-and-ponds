// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

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


// Overrides
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

	
// UProperties
public:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<AEnemyBase> LockedOnEnemy;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UGameplayAbility_Base>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|GAS")
	TArray<TSubclassOf<UAttributeSetBase>> DefaultAttributes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<USphereComponent> AttackSphere;


// Member Functions
private:
	void InitializeAbilities();
	void InitializeAttributes();


// Member Variables
private:
	TArray<TObjectPtr<AEnemyBase>> EnemiesInRange;
	
};
