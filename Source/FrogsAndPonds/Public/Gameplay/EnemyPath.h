// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyPath.generated.h"

class AEnemyBase;
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

USTRUCT(BlueprintType)
struct FEnemyPack
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<AEnemyBase> EnemyClass = AEnemyBase::StaticClass();
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int EnemyCount = 1;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float SpawnRate = 3.0;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float TimerDelay = 0.0;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool AwaitPreviousPacks = false;
};

USTRUCT(BlueprintType)
struct FEnemyWave
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FEnemyPack> EnemyPacks;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float NextWaveDelay = 0;
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

	
// Virtuals
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	
// Functions
private:
	void UpdateBillboardComponents();

	
// UProperties
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Custom")
	TArray<FEnemyWave> EnemyWaves;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Custom")
	TArray<int> Integer;
	
private:
	UPROPERTY(EditAnywhere, Category="Custom")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, Category="Custom")
	FDebugSpriteSettings StartPointSpriteSettings;

	UPROPERTY(EditAnywhere, Category="Custom")
	FDebugSpriteSettings EndPointSpriteSettings;

	
// Variables
private:
	TObjectPtr<UBillboardComponent> StartBillboardComponent;
	TObjectPtr<UBillboardComponent> EndBillboardComponent;
};
