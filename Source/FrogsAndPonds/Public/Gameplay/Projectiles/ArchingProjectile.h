// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Projectiles/ProjectileBase.h"
#include "ArchingProjectile.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FROGSANDPONDS_API AArchingProjectile : public AProjectileBase
{
	GENERATED_BODY()

	
// Lifecycle
protected:
	virtual void BeginPlay() override;

	
// Overrides
public:
	virtual void Tick(float DeltaTime) override;


// UProperties
private:
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float ArchingHeight = 200;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float ProjectileSpeed = 10;


// Variables
private:
	FVector StartPosition;
	float CurrentDistance = 0;
	
};
