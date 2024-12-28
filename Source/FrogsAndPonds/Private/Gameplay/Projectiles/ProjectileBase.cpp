// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/ProjectileBase.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(FName("IgnoreAll"));
	RootComponent = StaticMeshComponent;

	ProjectileSpeed = 10;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::InitTarget(const USceneComponent* ProjectileTarget)
{
	ProjectileTargetSceneComponent = ProjectileTarget;
}

FTargetStruck* AProjectileBase::GetTargetStruckDelegate()
{
	return &TargetStruckDelegate;
}
