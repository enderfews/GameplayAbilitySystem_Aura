// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}
void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}
void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		SpawnEffects();
	}

	Super::Destroyed();
}
void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnEffects();

	if (HasAuthority())
	{
		UAbilitySystemComponent* const TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		if (IsValid(TargetASC))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
		}

		Destroy();
	}
	else
	{
		bHit = true;
	}
}

void AAuraProjectile::SpawnEffects()
{
	LoopingSoundComponent->Stop();
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
}
