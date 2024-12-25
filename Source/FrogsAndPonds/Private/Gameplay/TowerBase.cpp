// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TowerBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/SphereComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Enemies/EnemyBase.h"
#include "GAS/Abilities/GameplayAbility_Base.h"
#include "GAS/Abilities/GameplayAbility_TowerAttack.h"
#include "GAS/Attributes/AttributeSetBase.h"
#include "GAS/Attributes/TowerAttributeSet.h"

// Sets default values
ATowerBase::ATowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(FName("AttackSphere"));
	RootComponent = AttackSphere;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(RootComponent);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));

	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnComponentBeginOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnComponentEndOverlap);

	DefaultAttributes.Add(UTowerAttributeSet::StaticClass());
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AbilitySystemComponent) return;

	InitializeAbilities();
	InitializeAttributes();	
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
	if (!OtherActor->IsA(AEnemyBase::StaticClass())) return;
	
	AEnemyBase* OtherEnemy = Cast<AEnemyBase>(OtherActor);
	EnemiesInRange.Add(OtherEnemy);
	if (!IsValid(LockedOnEnemy) || OtherEnemy->GetMoveDistance() < LockedOnEnemy->GetMoveDistance())
	{
		LockedOnEnemy = OtherEnemy;
	}
}

void ATowerBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->IsA(AEnemyBase::StaticClass())) return;
	
	AEnemyBase* OtherEnemy = Cast<AEnemyBase>(OtherActor);
	EnemiesInRange.Remove(OtherEnemy);

	if (OtherEnemy == LockedOnEnemy)
	{
		LockedOnEnemy = nullptr;
	}
}

void ATowerBase::InitializeAbilities()
{
	for (auto Ability : AttackAbilities)
	{
		if (!Ability) continue;
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(EAbilityInputID::None), this));
	}
	
	for (auto Ability : LockOnAbilities)
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

void ATowerBase::OnLockedOnEnemyChange(AEnemyBase* PreviousTarget, AEnemyBase* NewTarget)
{
	if (PreviousTarget && NewTarget) return;
	if (NewTarget)
	{
		AbilitySystemComponent->AddLooseGameplayTag(GTag_State_LockedOn);
	}
	else if (PreviousTarget)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(GTag_State_LockedOn);
	}
}

AEnemyBase* ATowerBase::GetLockedOnEnemy() const
{
	return TObjectPtr<AEnemyBase>(LockedOnEnemy);
}

float ATowerBase::GetAttackPower() const
{
	return AbilitySystemComponent->GetNumericAttribute(UTowerAttributeSet::GetAttackPowerAttribute());
}

float ATowerBase::GetAttackSpeed() const
{
	return AbilitySystemComponent->GetNumericAttribute(UTowerAttributeSet::GetAttackSpeedAttribute());
}
