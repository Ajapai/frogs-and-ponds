// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TowerBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/EnemyBase.h"
#include "Gameplay/Abilities/GameplayAbility_Base.h"
#include "Gameplay/Abilities/GameplayAbility_TowerAttack.h"
#include "Gameplay/Attributes/OffensiveAttributeSet.h"
#include "Gameplay/Attributes/AttributeSetBase.h"

// Sets default values
ATowerBase::ATowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(FName("AttackSphere"));
	AttackRangeSphere->SetCollisionProfileName(FName("OverlapAll"));
	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnComponentBeginOverlap);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnComponentEndOverlap);
	RootComponent = AttackRangeSphere;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(FName("IgnoreAll"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("BulletSpawnPoint"));
	BulletSpawnPoint->SetRelativeLocation(FVector(0, 0, 120));
	BulletSpawnPoint->SetupAttachment(RootComponent);

	AttackRangeDecal = CreateDefaultSubobject<UDecalComponent>(FName("AttackRangeDecal"));
	AttackRangeDecal->SetRelativeRotation(FRotator(90, 0, 0));
	AttackRangeDecal->DecalSize = FVector(1, 400, 400);
	AttackRangeDecal->SetupAttachment(RootComponent);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));

	DefaultAttributes.Add(UOffensiveAttributeSet::StaticClass());
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AbilitySystemComponent) return;

	InitializeAbilities();
	InitializeAttributes();

	UpdateAttackRange();
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
	
	if (EnemiesInRange.Num() == 1)
	{
		AbilitySystemComponent->AddLooseGameplayTag(GTag_State_EnemyInRange);
	}
}

void ATowerBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->IsA(AEnemyBase::StaticClass())) return;
	
	AEnemyBase* OtherEnemy = Cast<AEnemyBase>(OtherActor);
	EnemiesInRange.Remove(OtherEnemy);

	if (EnemiesInRange.Num() == 0)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(GTag_State_EnemyInRange);
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
}

void ATowerBase::InitializeAttributes()
{
	for (auto AttributeSetType : DefaultAttributes)
	{
		AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UAttributeSetBase>(this, AttributeSetType));
	}

	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackPowerAttribute(), OffensiveAttributes.AttackPower);
	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackRangeAttribute(), OffensiveAttributes.AttackRange);
	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackSpeedAttribute(), OffensiveAttributes.AttackSpeed);
}

void ATowerBase::UpdateAttackRange() const
{
	AttackRangeSphere->SetSphereRadius(GetAttackRange());
	AttackRangeDecal->DecalSize = FVector(1, GetAttackRange(), GetAttackRange());
	AttackRangeDecal->MarkRenderStateDirty();
}

float ATowerBase::GetAttackPower() const
{
	return AbilitySystemComponent->GetNumericAttribute(UOffensiveAttributeSet::GetAttackPowerAttribute());
}

float ATowerBase::GetAttackSpeed() const
{
	return AbilitySystemComponent->GetNumericAttribute(UOffensiveAttributeSet::GetAttackSpeedAttribute());
}

float ATowerBase::GetAttackRange() const
{
	return AbilitySystemComponent->GetNumericAttribute(UOffensiveAttributeSet::GetAttackRangeAttribute());
}

const USceneComponent* ATowerBase::GetBulletSpawnPoint() const
{
	return BulletSpawnPoint;
}
