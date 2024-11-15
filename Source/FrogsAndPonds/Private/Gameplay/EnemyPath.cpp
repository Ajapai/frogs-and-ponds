// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyPath.h"

#include "Components/BillboardComponent.h"
#include "Components/SplineComponent.h"
#include "Engine/TargetPoint.h"

AEnemyPath::AEnemyPath()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("SplineComponent"));
	RootComponent = SplineComponent;
	
	StartBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(FName("BillboardStart"));
	StartBillboardComponent->SetupAttachment(RootComponent);
	StartBillboardComponent->bIsEditorOnly = true;

	EndBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(FName("BillboardEnd"));
	EndBillboardComponent->SetupAttachment(RootComponent);
	EndBillboardComponent->bIsEditorOnly = true;
	
}

void AEnemyPath::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemyPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
#if WITH_EDITOR
	StartBillboardComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World) + FVector::UpVector * 10);
	EndBillboardComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(
		SplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World) + FVector::UpVector * 10);
#endif
}
