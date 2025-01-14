// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
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

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FRotator ProjectileOrientation = (ProjectileTargetLocation - SocketLocation).Rotation();
	ProjectileOrientation.Pitch = 0.f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(ProjectileOrientation.Quaternion());

	AAuraProjectile* const Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass
		, SpawnTransform
		, GetOwningActorFromActorInfo()
		, Cast<APawn>(GetOwningActorFromActorInfo())
		, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* const SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	Projectile->DamageSpecHandle = SpecHandle;
	Projectile->FinishSpawning(SpawnTransform);
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
