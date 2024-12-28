// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Projectiles/ProjectileBase.h"
#include "TargetProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API ATargetProjectile : public AProjectileBase
{
	GENERATED_BODY()


// Overrides
public:
	virtual void Tick(float DeltaTime) override;
	
};
