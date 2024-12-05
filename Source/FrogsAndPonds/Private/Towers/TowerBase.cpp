// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/SphereComponent.h"
#include "Gameplay/AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "Gameplay/AbilitySystem/Attributes/BaseAttributeSet.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(FName("AttackSphere"));
	RootComponent = AttackSphere;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ATowerBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATowerBase::InitializeAbilities()
{
	for (auto Ability : DefaultAbilities)
	{
		if (!Ability) continue;
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(EAbilityInputID::None), this));
	}
}

void ATowerBase::InitializeAttributes()
{
	for (auto AttributeSetType : DefaultAttributes)
	{
		AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UBaseAttributeSet>(this, AttributeSetType));
	}
}
