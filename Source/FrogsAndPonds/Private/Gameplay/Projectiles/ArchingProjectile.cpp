// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/ArchingProjectile.h"

void AArchingProjectile::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();
}

void AArchingProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDistance += DeltaTime * ProjectileSpeed;
	if (CurrentDistance >= 1)
	{
		AssignedTargetStruck();
		Destroy();
	}

	FVector NextPosition = FMath::Lerp(StartPosition, TargetSceneComponent->GetComponentLocation(), CurrentDistance);
	NextPosition.Z += FMath::Sin(CurrentDistance * PI) * ArchingHeight;

	SetActorRotation((NextPosition - GetActorLocation()).Rotation());
	SetActorLocation(NextPosition);
}
