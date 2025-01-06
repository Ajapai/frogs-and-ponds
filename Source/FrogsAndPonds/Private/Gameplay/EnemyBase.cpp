// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Abilities/GameplayAbility_Move.h"
#include "Gameplay/Attributes/OffensiveAttributeSet.h"
#include "Gameplay/Attributes/DefensiveAttributeSet.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("SphereComponent"));
	CapsuleComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));
	RootComponent = CapsuleComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(FName("IgnoreAll"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileTarget = CreateDefaultSubobject<USceneComponent>(FName("ProjectileTarget"));
	ProjectileTarget->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));

	DefaultAbilities.Add(UGameplayAbility_Move::StaticClass());
	DefaultAttributes.Add(UDefensiveAttributeSet::StaticClass());
	DefaultAttributes.Add(UOffensiveAttributeSet::StaticClass());
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	SplineComponent = Cast<USplineComponent>(GetOwner()->GetComponentByClass(USplineComponent::StaticClass())); 
	SetActorLocation(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	
	// SplineComponent = Cast<USplineComponent>(EnemyPath->GetComponentByClass(USplineComponent::StaticClass()));
	// SetActorLocation(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	
	if (!AbilitySystemComponent) return;

	InitializeAbilities();
	InitializeAttributes();

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag_Ability_Move));
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDefensiveAttributeSet::GetHealthAttribute()).
	                        AddUObject(this, &AEnemyBase::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDefensiveAttributeSet::GetPredictedHealthAttribute()).
						AddUObject(this, &AEnemyBase::PredictedHealthChanged);
}

UAbilitySystemComponent* AEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AbilitySystemComponent->HasMatchingGameplayTag(GTag_Ability_Move))
	{
		MoveDistance += DeltaTime * 15 * GetMoveSpeed(); 
		SetActorLocation(SplineComponent->GetLocationAtDistanceAlongSpline(MoveDistance, ESplineCoordinateSpace::World));
	}
}

void AEnemyBase::InitializeAbilities()
{
	for (auto Ability : DefaultAbilities)
	{
		if (!Ability) continue;
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(EAbilityInputID::None), this));
	}
}

void AEnemyBase::InitializeAttributes()
{
	for (auto AttributeSetType : DefaultAttributes)
	{
		AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UAttributeSetBase>(this, AttributeSetType));
	}
	
	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackPowerAttribute(), OffensiveAttributes.AttackPower);
	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackRangeAttribute(), OffensiveAttributes.AttackRange);
	AbilitySystemComponent->SetNumericAttributeBase(UOffensiveAttributeSet::GetAttackSpeedAttribute(), OffensiveAttributes.AttackSpeed);
	AbilitySystemComponent->SetNumericAttributeBase(UDefensiveAttributeSet::GetMoveSpeedAttribute(), DefensiveAttributes.MoveSpeed);
	AbilitySystemComponent->SetNumericAttributeBase(UDefensiveAttributeSet::GetMaxHealthAttribute(), DefensiveAttributes.MaxHealth);
	AbilitySystemComponent->SetNumericAttributeBase(UDefensiveAttributeSet::GetHealthAttribute(), DefensiveAttributes.MaxHealth);
	AbilitySystemComponent->SetNumericAttributeBase(UDefensiveAttributeSet::GetPredictedHealthAttribute(), DefensiveAttributes.MaxHealth);
}

void AEnemyBase::HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	OnHealthChanged(OnAttributeChangeData.OldValue, OnAttributeChangeData.NewValue);
	if (OnAttributeChangeData.NewValue <= 0) Destroy();
}

void AEnemyBase::PredictedHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	if (OnAttributeChangeData.NewValue <= 0)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

float AEnemyBase::GetHealth() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefensiveAttributeSet::GetHealthAttribute());
}

float AEnemyBase::GetMaxHealth() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefensiveAttributeSet::GetMaxHealthAttribute());
}

float AEnemyBase::GetMoveSpeed() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefensiveAttributeSet::GetMoveSpeedAttribute());
}

float AEnemyBase::GetMoveDistance() const
{
	return MoveDistance;
}

const USceneComponent* AEnemyBase::GetProjectileTarget()
{
	return ProjectileTarget;
}
