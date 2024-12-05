// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/EnemyPath.h"
#include "Gameplay/AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "Gameplay/AbilitySystem/Attributes/EnemyAttributeSet.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
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
}

UAbilitySystemComponent* AEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FString message = FString::Printf(
	// 	TEXT("Distance: %f, MaxDistance: %f"),
	// 	AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetDistanceAttribute()),
	// 	AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetMaxDistanceAttribute()));
	//
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, message, true, {1, 1});

	if (AbilitySystemComponent->HasMatchingGameplayTag(GTag_Ability_Move))
	{
		
	AbilitySystemComponent->SetNumericAttributeBase(UEnemyAttributeSet::GetDistanceAttribute(),
	                                                AbilitySystemComponent->GetNumericAttribute(
		                                                UEnemyAttributeSet::GetDistanceAttribute()) + DeltaTime * 300);

	SetActorLocation(SplineComponent->GetLocationAtDistanceAlongSpline(
		AbilitySystemComponent->GetNumericAttribute(UEnemyAttributeSet::GetDistanceAttribute()),
		ESplineCoordinateSpace::World));
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
		AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UBaseAttributeSet>(this, AttributeSetType));
	}

	AbilitySystemComponent->SetNumericAttributeBase(UEnemyAttributeSet::GetMaxDistanceAttribute(), SplineComponent->GetSplineLength());
}
