// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class FROGSANDPONDS_API AMainHUD : public AHUD
{
	GENERATED_BODY()


// Overrides
public:
	virtual void GetDebugActorList(TArray<AActor*>& InOutList) override;
};
