// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Aura/Public/AbilitySystem/AuraAttributeSet.h"
#include "Components/StaticMeshComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* const ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (ASCInterface == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* const GASComp = ASCInterface->GetAbilitySystemComponent();
	if (!IsValid(GASComp))
	{
		return;
	}

	//TODO: Change this to appply Gameplay Effect
	const UAuraAttributeSet* const AuraAttributeSet = Cast<UAuraAttributeSet>(GASComp->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	UAuraAttributeSet* const mutableAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
	if (!IsValid(mutableAttributeSet))
	{
		return;
	}

	mutableAttributeSet->SetHealth(mutableAttributeSet->GetHealth() + 25.f);
	Destroy();
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

