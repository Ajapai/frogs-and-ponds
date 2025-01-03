// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameplayTagsDeclaration.h"

// Abilities
UE_DEFINE_GAMEPLAY_TAG(GTag_Ability, "Ability");
UE_DEFINE_GAMEPLAY_TAG(GTag_Ability_Test, "Ability.Test");
UE_DEFINE_GAMEPLAY_TAG(GTag_Ability_Move, "Ability.Move");
UE_DEFINE_GAMEPLAY_TAG(GTag_Ability_Attack, "Ability.Attack");

// Status
UE_DEFINE_GAMEPLAY_TAG(GTag_Status_Stun, "Status.Stun");

// State
UE_DEFINE_GAMEPLAY_TAG(GTag_State_LockedOn, "State.LockedOn");
UE_DEFINE_GAMEPLAY_TAG(GTag_State_EnemyInRange, "State.EnemyInRange");
UE_DEFINE_GAMEPLAY_TAG(GTag_State_Active, "State.Active");

// SetByCaller Tags 
UE_DEFINE_GAMEPLAY_TAG(GTag_SetByCaller_Amount, "SetByCaller.Amount");
UE_DEFINE_GAMEPLAY_TAG(GTag_SetByCaller_Duration, "SetByCaller.Duration");
