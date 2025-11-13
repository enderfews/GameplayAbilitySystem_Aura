// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/Public/AuraGameplayTags.h"

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	AActor* const AvatarActor = GetAvatarActorFromActorInfo();
	const bool bIsServer = AvatarActor->HasAuthority();
	if (!bIsServer)
	{
		return;
	}

	if (!AvatarActor->Implements<UCombatInterface>())
	{
		return;
	}

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(AvatarActor);
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

	const UAbilitySystemComponent* const SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor);
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, Damage.GetValueAtLevel(GetAbilityLevel()));
	Projectile->DamageSpecHandle = SpecHandle;
	Projectile->FinishSpawning(SpawnTransform);
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
