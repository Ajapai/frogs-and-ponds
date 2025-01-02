// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/TargetProjectile.h"

void ATargetProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileTargetSceneComponent == nullptr)
	{
		Destroy();
		return;
	}

	const FVector Direction = ProjectileTargetSceneComponent->GetComponentLocation() - GetActorLocation();

	if (Direction.Length() < 10)
	{
		TargetStruckDelegate.Execute(Cast<IAbilitySystemInterface>(ProjectileTargetSceneComponent->GetOwner())->GetAbilitySystemComponent());
		Destroy();
	}
	
	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal() * ProjectileSpeed * 50 * DeltaTime);
}

// void ATargetProjectile::InitTarget(TWeakObjectPtr<USceneComponent> TargetSceneComponent)
// {
// 	Super::InitTarget(TargetSceneComponent);
// }
