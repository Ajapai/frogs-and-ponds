// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/SphereComponent.h"
#include "Enemies/EnemyBase.h"
#include "Gameplay/AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "Gameplay/AbilitySystem/Attributes/AttributeSetBase.h"

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

	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnComponentBeginOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnComponentEndOverlap);
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

void ATowerBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Enter", true, {1, 1});
	if (OtherActor->IsA(AEnemyBase::StaticClass()))
	{
		EnemiesInRange.Add(Cast<AEnemyBase>(OtherActor));
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "In Range", true, {1, 1});
	}

}

void ATowerBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Leave", true, {1, 1});
	if (OtherActor->IsA(AEnemyBase::StaticClass()))
	{
		EnemiesInRange.Remove(Cast<AEnemyBase>(OtherActor));
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Out Of Range", true, {1, 1});
	}
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
		AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UAttributeSetBase>(this, AttributeSetType));
	}
}
