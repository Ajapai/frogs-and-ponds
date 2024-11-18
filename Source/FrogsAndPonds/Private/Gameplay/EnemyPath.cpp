// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyPath.h"

#include "Components/BillboardComponent.h"
#include "Components/SplineComponent.h"


AEnemyPath::AEnemyPath()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("SplineComponent"));
	RootComponent = SplineComponent;
	SplineComponent->bShouldVisualizeScale = true;
	SplineComponent->EditorUnselectedSplineSegmentColor = FColor(0xFFFF0000);
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> StartSprite(TEXT("/Engine/EngineResources/AICON-Red.AICON-Red"));
	if (StartSprite.Object)
	{
		StartPointSpriteSettings.Texture = StartSprite.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> EndSprite(TEXT("/Engine/MobileResources/HUD/AnalogHat.AnalogHat"));
	if (EndSprite.Object)
	{
		EndPointSpriteSettings.Texture = EndSprite.Object;
	}
	EndPointSpriteSettings.Scale.Z = 1.5f;
}

void AEnemyPath::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEnemyPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateBillboardComponents();
}

void AEnemyPath::UpdateBillboardComponents()
{
#if WITH_EDITOR
	if (!StartBillboardComponent)
	{
		StartBillboardComponent = NewObject<UBillboardComponent>(this);
		StartBillboardComponent->SetupAttachment(RootComponent);
		StartBillboardComponent->RegisterComponent();
		StartBillboardComponent->bIsEditorOnly = true;
	}

	if (!EndBillboardComponent)
	{
		EndBillboardComponent = NewObject<UBillboardComponent>(this);
		EndBillboardComponent->SetupAttachment(RootComponent);
		EndBillboardComponent->RegisterComponent();
		EndBillboardComponent->bIsEditorOnly = true;
	}
	
	StartBillboardComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(
		0, ESplineCoordinateSpace::World) + StartPointSpriteSettings.Offset);
	StartBillboardComponent->SetSprite(StartPointSpriteSettings.Texture);
	StartBillboardComponent->SetWorldScale3D(StartPointSpriteSettings.Scale);
	
	EndBillboardComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(
		SplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World) + EndPointSpriteSettings.Offset);
	EndBillboardComponent->SetSprite(EndPointSpriteSettings.Texture);
	EndBillboardComponent->SetWorldScale3D(EndPointSpriteSettings.Scale);


	if (SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local) == FVector::Zero()) return;
	
	const FVector Offset = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	SplineComponent->SetWorldLocation(SplineComponent->GetComponentLocation() + Offset);
	for (int i = 0; i < SplineComponent->GetNumberOfSplinePoints(); i++)
	{
		SplineComponent->SetLocationAtSplinePoint(
			i,
			SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local) - Offset,
			ESplineCoordinateSpace::Local
		);
	}
#endif
}
