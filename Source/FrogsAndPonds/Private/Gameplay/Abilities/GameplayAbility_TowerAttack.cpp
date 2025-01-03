// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/GameplayAbility_TowerAttack.h"

#include "Core/GameplayTagsDeclaration.h"
#include "Gameplay/EnemyBase.h"
#include "Gameplay/TowerBase.h"
#include "Gameplay/Attributes/OffensiveAttributeSet.h"
#include "Gameplay/Projectiles/ProjectileBase.h"
#include "Helpers/ApplyEffectsFunctionLibrary.h"

UGameplayAbility_TowerAttack::UGameplayAbility_TowerAttack(): OwningTower(nullptr), TimerManager(nullptr)
{
	FAbilityTriggerData AbilityTriggerData;
	AbilityTriggerData.TriggerTag = GTag_State_EnemyInRange;
	AbilityTriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	AbilityTriggers.Add(AbilityTriggerData);

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	AttackTimerDelegate.BindUObject(this, &UGameplayAbility_TowerAttack::OnAttackReady);
}

void UGameplayAbility_TowerAttack::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	OwningTower = Cast<ATowerBase>(ActorInfo->OwnerActor);
	TimerManager = &GetWorld()->GetTimerManager();
	
	ActorInfo->AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UOffensiveAttributeSet::GetAttackSpeedAttribute())
	.AddUObject(this, &UGameplayAbility_TowerAttack::OnAttackSpeedChanged);
}

void UGameplayAbility_TowerAttack::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	OwningTower = nullptr;
	TimerManager = nullptr;
	
	ActorInfo->AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UOffensiveAttributeSet::GetAttackSpeedAttribute()).RemoveAll(this);
}

void UGameplayAbility_TowerAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	}
	
	if (TimerManager->IsTimerActive(AttackTimer)) return;

	OnAttackReady();
}

void UGameplayAbility_TowerAttack::EndAbility(const FGameplayAbilitySpecHandle Handle,
											  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
											  bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_TowerAttack::OnAttackReady()
{
	if (!IsActive()) return;
	
	TimerManager->SetTimer(AttackTimer, AttackTimerDelegate, OwningTower->GetAttackSpeed(), false);
	StartAttack();
}

void UGameplayAbility_TowerAttack::StartAttack()
{
#if WITH_EDITOR
	if (ProjectileClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%s Projectile Class is Empty"), *this->GetName()), true, {1, 1});
		return;
	}
#endif

	FVector Location = OwningTower->GetBulletSpawnPoint()->GetComponentLocation();
	FRotator Rotation = FRotator::ZeroRotator;
	AEnemyBase* CurrentTarget = GetCurrentTarget();
	
	AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
	SpawnedProjectile->GetTargetStruckDelegate()->BindUObject(this, &UGameplayAbility_TowerAttack::TargetStruck);
	SpawnedProjectile->Init(CurrentTarget->GetProjectileTarget(), GetDamageValue());
	
	if (bDamageIsPredictable)
	{
		UApplyEffectsFunctionLibrary::ApplyDamagePredictionToTarget(CurrentTarget->GetAbilitySystemComponent(), this, GetDamageValue());
	}
}

void UGameplayAbility_TowerAttack::TargetStruck(UAbilitySystemComponent* TargetAsc, const float ProjectileDamage)
{
	if (bDamageIsPredictable)
	{
		UApplyEffectsFunctionLibrary::ApplyPredictedDamageToTarget(TargetAsc, this, ProjectileDamage);
	}
	else
	{
		UApplyEffectsFunctionLibrary::ApplyUnpredictedDamageToTarget(TargetAsc, this, ProjectileDamage);
	}
	OnTargetStruck(TargetAsc);
}

void UGameplayAbility_TowerAttack::OnAttackSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
}

float UGameplayAbility_TowerAttack::GetDamageValue() const
{
	return BaseDamage;
}

AEnemyBase* UGameplayAbility_TowerAttack::GetCurrentTarget() const
{
	if (TargetingMethod == ETargetingMethod::Random)
	{
		return OwningTower->EnemiesInRange[FMath::RandRange(0, OwningTower->EnemiesInRange.Num() - 1)];
	}

	OwningTower->EnemiesInRange.Sort();
	return TargetingMethod == ETargetingMethod::First ? OwningTower->EnemiesInRange.Top() : OwningTower->EnemiesInRange[0];
}
