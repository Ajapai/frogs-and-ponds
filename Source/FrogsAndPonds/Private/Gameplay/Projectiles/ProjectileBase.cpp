// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/ProjectileBase.h"

#include "Components/SphereComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	SphereComponent->SetCollisionProfileName(FName("IgnoreAll"));
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(FName("IgnoreAll"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::Init(const USceneComponent* ProjectileTargetSceneComponent, const float ProjectileDamage)
{
	TargetSceneComponent = ProjectileTargetSceneComponent;
	Damage = ProjectileDamage;

	PostInit();
}

FTargetStruck* AProjectileBase::GetTargetStruckDelegate()
{
	return &TargetStruckDelegate;
}

void AProjectileBase::AssignedTargetStruck() const
{
	TargetStruckDelegate.Execute(Cast<IAbilitySystemInterface>(TargetSceneComponent->GetOwner())->GetAbilitySystemComponent(), Damage);
}
