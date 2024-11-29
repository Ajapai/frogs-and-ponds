// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "EnemyBase.generated.h"

class UBaseGameplayAbility;

UCLASS()
class FROGSANDPONDS_API AEnemyBase : public AActor, public IAbilitySystemInterface 
{
	GENERATED_BODY()

	
	// Constructor
public:	
	AEnemyBase();


	// Overrides
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void AfterBeginPlay();

	
	// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TArray<TSubclassOf<UBaseGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
private:
	UPROPERTY(EditAnywhere, Category="Custom")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
