// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface)
	{
		return;
	}


	FTransform SpawnTransform;
	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	//TODO: Set projectile rotation

	AAuraProjectile* const Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass
		, SpawnTransform
		, GetOwningActorFromActorInfo()
		, Cast<APawn>(GetOwningActorFromActorInfo())
		, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: Give the projectile a gameplay effect spec to the projectile
	Projectile->FinishSpawning(SpawnTransform);
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}