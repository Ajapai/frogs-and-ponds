// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class FROGSANDPONDS_API AProjectileBase : public AActor
{
	GENERATED_BODY()


// Lifecycle
public:	
	AProjectileBase();

protected:
	virtual void BeginPlay() override;


// Overrides
public:
	virtual void Tick(float DeltaTime) override;

};
