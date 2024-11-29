// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyBase.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Abilities/BaseGameplayAbility.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));

}

UAbilitySystemComponent* AEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AbilitySystemComponent) return;
	
	for (auto Ability : DefaultAbilities)
	{
		if (!Ability) continue;
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(EAbilityInputID::None), this));
	}
	
	AfterBeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

