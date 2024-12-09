// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPath.generated.h"

class ATargetPoint;
class UBillboardComponent;
class USplineComponent;


USTRUCT(BlueprintType)
struct FDebugSpriteSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Texture = nullptr;
	UPROPERTY(EditAnywhere)
	FVector Offset = FVector(0,0,30.0f);
	UPROPERTY(EditAnywhere)
	FVector Scale = FVector::OneVector;
};

UCLASS()
class FROGSANDPONDS_API AEnemyPath : public AActor
{
	GENERATED_BODY()

	
// Lifecycle
public:	
	AEnemyPath();

protected:
	virtual void BeginPlay() override;

	
// Overrides
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	
// UProperties
private:
	UPROPERTY(EditAnywhere, Category="Custom|Components")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, Category="Custom|DebugSprites")
	FDebugSpriteSettings StartPointSpriteSettings;

	UPROPERTY(EditAnywhere, Category="Custom|DebugSprites")
	FDebugSpriteSettings EndPointSpriteSettings;


// Member Functions
private:
	void UpdateBillboardComponents();

	
// Member Pointers
private:
	TObjectPtr<UBillboardComponent> StartBillboardComponent;
	TObjectPtr<UBillboardComponent> EndBillboardComponent;
};
