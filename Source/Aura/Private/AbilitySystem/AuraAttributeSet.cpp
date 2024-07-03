// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewValue);
	}

	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Health: %f"), NewValue);
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);
	}

	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Mana: %f"), NewValue);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);



}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& oldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, oldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, oldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, oldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, oldMaxMana);
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	//Source: causer of the effect. 
	//Target: target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* const SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(SourceASC))
	{
		Props.Source.ASC = SourceASC;
	}

	FGameplayAbilityActorInfo* const SourceActorInfo = (IsValid(SourceASC))? SourceASC->AbilityActorInfo.Get() : nullptr;
	AActor* const SourceAvatarActor = (SourceActorInfo != nullptr)? SourceActorInfo->AvatarActor.Get() : nullptr;
	if (IsValid(SourceAvatarActor))
	{
		Props.Source.AvatarActor = SourceAvatarActor;
	}

	AController* SourceController = (SourceActorInfo != nullptr) ? SourceActorInfo->PlayerController.Get() : nullptr;
	if (!IsValid(SourceController))
	{
		APawn* const SourcePawn = Cast<APawn>(SourceAvatarActor);
		if (IsValid(SourcePawn))
		{
			SourceController = SourcePawn->GetController();
		}
	}

	if (IsValid(SourceController))
	{
		Props.Source.Controller = SourceController;
	}

	ACharacter* const SourceCharacter = (IsValid(SourceController))? Cast<ACharacter>(SourceController->GetPawn()) : nullptr;
	if (IsValid(SourceCharacter))
	{
		Props.Source.Character = SourceCharacter;
	}

	FGameplayAbilityActorInfo* const TargetActorInfo = Data.Target.AbilityActorInfo.Get();
	AActor* const TargetAvatarActor = (TargetActorInfo != nullptr)? TargetActorInfo->AvatarActor.Get() : nullptr;
	if (IsValid(TargetAvatarActor))
	{
		Props.Target.AvatarActor = TargetAvatarActor;
	}

	AController* const TargetController = (TargetActorInfo != nullptr) ? TargetActorInfo->PlayerController.Get() : nullptr;
	if (IsValid(TargetController))
	{
		Props.Target.Controller = TargetController;
	}

	ACharacter* const TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
	if (IsValid(TargetCharacter))
	{
		Props.Target.Character = TargetCharacter;
	}

	UAbilitySystemComponent* const TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
	if (IsValid(TargetASC))
	{
		Props.Target.ASC = TargetASC;
	}
}
