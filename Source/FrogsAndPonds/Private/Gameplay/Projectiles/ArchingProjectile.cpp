// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Projectiles/ArchingProjectile.h"

void AArchingProjectile::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();
}

void AArchingProjectile::PostInit()
{
	// const float DistanceToTarget = (StartPosition - TargetSceneComponent->GetComponentLocation()).Length();
	//
	// ArchingHeight = FMath::GetMappedRangeValueClamped(FVector2d(0, Range), FVector2d(MaxArch, MinArch), DistanceToTarget);
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

	if (IsValid(TargetSceneComponent))
	{
		TargetLocation = TargetSceneComponent->GetComponentLocation();
	}

	FVector NextPosition = FMath::Lerp(StartPosition, TargetLocation, CurrentDistance);
	NextPosition.Z += FMath::Sin(CurrentDistance * PI) * ArchingHeight;

	SetActorRotation((NextPosition - GetActorLocation()).Rotation());
	SetActorLocation(NextPosition);
}
