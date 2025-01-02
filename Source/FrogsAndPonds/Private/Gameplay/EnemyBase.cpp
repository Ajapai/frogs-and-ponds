// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/Abilities/GameplayAbility_Move.h"
#include "Gameplay/Attributes/AttackerAttributeSet.h"
#include "Gameplay/Attributes/DefenderAttributeSet.h"


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
	DefaultAttributes.Add(UDefenderAttributeSet::StaticClass());
	DefaultAttributes.Add(UAttackerAttributeSet::StaticClass());
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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDefenderAttributeSet::GetHealthAttribute()).
	                        AddUObject(this, &AEnemyBase::HealthChanged);
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
}

void AEnemyBase::HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	OnHealthChanged(OnAttributeChangeData.OldValue, OnAttributeChangeData.NewValue);
	if (OnAttributeChangeData.NewValue <= 0) Destroy();
}

float AEnemyBase::GetHealth() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefenderAttributeSet::GetHealthAttribute());
}

float AEnemyBase::GetMaxHealth() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefenderAttributeSet::GetMaxHealthAttribute());
}

float AEnemyBase::GetMoveSpeed() const
{
	return AbilitySystemComponent->GetNumericAttribute(UDefenderAttributeSet::GetMoveSpeedAttribute());
}

float AEnemyBase::GetMoveDistance() const
{
	return MoveDistance;
}

const USceneComponent* AEnemyBase::GetProjectileTarget()
{
	return ProjectileTarget;
}
