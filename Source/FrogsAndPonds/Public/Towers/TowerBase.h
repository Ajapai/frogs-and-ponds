// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

class USphereComponent;
class UBaseAttributeSet;
class UBaseGameplayAbility;

UCLASS()
class FROGSANDPONDS_API ATowerBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()


	// Lifecycle
public:	
	ATowerBase();

protected:
	virtual void BeginPlay() override;


	// Inheritance
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;

	
	// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TArray<TSubclassOf<UBaseGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TArray<TSubclassOf<UBaseAttributeSet>> DefaultAttributes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<USphereComponent> AttackSphere;


	// Member Functions
	void InitializeAbilities();
	void InitializeAttributes();
	
};
