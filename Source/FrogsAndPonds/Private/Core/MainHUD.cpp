// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainHUD.h"

#include "EngineUtils.h"
#include "Enemies/EnemyBase.h"
#include "Towers/TowerBase.h"

void AMainHUD::GetDebugActorList(TArray<AActor*>& InOutList)
{
	Super::GetDebugActorList(InOutList);
	
	UWorld* World = GetWorld();

	// By default, add all Pawns.
	for (TActorIterator<AEnemyBase> It(World); It; ++It)
	{
		AddActorToDebugList(*It, InOutList, World);
	}

	for (TActorIterator<ATowerBase> It(World); It; ++It)
	{
		AddActorToDebugList(*It, InOutList, World);
	}
}
