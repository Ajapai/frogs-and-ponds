// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
DECLARE_DELEGATE_TwoParams(FTargetStruck, UAbilitySystemComponent*, float);

UCLASS(Abstract)
class FROGSANDPONDS_API AProjectileBase : public AActor
{
	GENERATED_BODY()


// Lifecycle
public:	
	AProjectileBase();

protected:
	virtual void BeginPlay() override;


// Virtuals
public:
	virtual void Init(const USceneComponent* ProjectileTargetSceneComponent, float ProjectileDamage = 0);
	
protected:
	virtual void PostInit() PURE_VIRTUAL();


// Accessors
public:
	FTargetStruck* GetTargetStruckDelegate();


// Functions
protected:
	void AssignedTargetStruck() const;
	
// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly)
	const USceneComponent* TargetSceneComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<USphereComponent> SphereComponent;

// Variables
protected:
	FTargetStruck TargetStruckDelegate;
	float Damage;
};
