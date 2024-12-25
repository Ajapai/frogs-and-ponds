// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/EnemyPath.h"
#include "GAS/Abilities/GameplayAbility_Move.h"
#include "GAS/Attributes/EnemyAttributeSet.h"


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

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));

	DefaultAbilities.Add(UGameplayAbility_Move::StaticClass());
	DefaultAttributes.Add(UEnemyAttributeSet::StaticClass());
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	SplineComponent = Cast<USplineComponent>(EnemyPath->GetComponentByClass(USplineComponent::StaticClass()));
	SetActorLocation(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	
	if (!AbilitySystemComponent) return;

	InitializeAbilities();
	InitializeAttributes();

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GTag_Ability_Move));
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute()).
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
		SetMoveDistance(GetMoveDistance() + DeltaTime * 300);
		SetActorLocation(SplineComponent->GetLocationAtDistanceAlongSpline(GetMoveDistance(), ESplineCoordinateSpace::World));
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

	AbilitySystemComponent->SetNumericAttributeBase(UEnemyAttributeSet::GetMaxMoveDistanceAttribute(), SplineComponent->GetSplineLength());
}

void AEnemyBase::HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (OnAttributeChangeData.NewValue <= 0) Destroy();
}
float AEnemyBase::GetHealth() const
{
	return AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetHealthAttribute());
}

float AEnemyBase::GetMoveDistance() const
{
	return AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetMoveDistanceAttribute());
}

float AEnemyBase::GetMoveSpeed() const
{
	return AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetMoveSpeedAttribute());
}

void AEnemyBase::SetMoveDistance(const float& NewValue) const
{
	AbilitySystemComponent->SetNumericAttributeBase(UEnemyAttributeSet::GetMoveDistanceAttribute(), NewValue);	
}
