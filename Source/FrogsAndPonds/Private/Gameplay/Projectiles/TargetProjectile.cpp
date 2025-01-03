// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/TargetProjectile.h"

void ATargetProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetSceneComponent == nullptr)
	{
		Destroy();
		return;
	}

	const FVector Direction = TargetSceneComponent->GetComponentLocation() - GetActorLocation();

	if (Direction.Length() < 10)
	{
		AssignedTargetStruck();
		Destroy();
	}
	
	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal() * ProjectileSpeed * 50 * DeltaTime);
}

// void ATargetProjectile::InitTarget(TWeakObjectPtr<USceneComponent> TargetSceneComponent)
// {
// 	Super::InitTarget(TargetSceneComponent);
// }
