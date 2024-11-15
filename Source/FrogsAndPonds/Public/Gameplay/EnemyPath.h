// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPath.generated.h"

class ATargetPoint;
class UBillboardComponent;
class USplineComponent;

UCLASS()
class FROGSANDPONDS_API AEnemyPath : public AActor
{
	GENERATED_BODY()

	
// Constructors
public:	
	AEnemyPath();

	
// Overrides
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	
// UProperties
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBillboardComponent> StartBillboardComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBillboardComponent> EndBillboardComponent;
	
};
