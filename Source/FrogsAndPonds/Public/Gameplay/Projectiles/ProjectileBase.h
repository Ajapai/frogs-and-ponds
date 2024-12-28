// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FTargetStruck, AActor*, Target);

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
	virtual void InitTarget(const USceneComponent* ProjectileTarget);


// Accessors
public:
	FTargetStruck* GetTargetStruckDelegate();
	
// UProperties
protected:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Values")
	float ProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, Category="Custom|Values")
	FTargetStruck TargetStruckDelegate;

	UPROPERTY(BlueprintReadOnly, Category="Custom|Values")
	const USceneComponent* ProjectileTargetSceneComponent;
};
