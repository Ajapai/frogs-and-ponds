// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "EnemyBase.generated.h"

class UBaseAttributeSet;
class AEnemyPath;
class USplineComponent;
class UBaseGameplayAbility;

UCLASS()
class FROGSANDPONDS_API AEnemyBase : public AActor, public IAbilitySystemInterface 
{
	GENERATED_BODY()

	
	// Lifecycle
public:	
	AEnemyBase();

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
	
	UPROPERTY(EditInstanceOnly, Category="Custom")
	TObjectPtr<const AEnemyPath> EnemyPath;


	// Member Functions
	void InitializeAbilities();

	void InitializeAttributes();
	

	// Member Pointers
	TWeakObjectPtr<USplineComponent> SplineComponent;
};
