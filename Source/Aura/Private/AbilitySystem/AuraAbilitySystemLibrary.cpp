// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Player/AuraPlayerState.h"
#include "Game/AuraGameModeBase.h"
#include "UI/HUD/AuraHUD.h"
#include "AbilitySystemComponent.h"


UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* const PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC))
	{
		return nullptr;
	}

	AAuraHUD* const AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!IsValid(AuraHUD))
	{
		return nullptr;
	}

	AAuraPlayerState* const PlayerState = PC->GetPlayerState<AAuraPlayerState>();
	if (!IsValid(PlayerState))
	{
		return nullptr;
	}

	UAbilitySystemComponent* const ASC = PlayerState->GetAbilitySystemComponent();
	UAttributeSet* const AS = PlayerState->GetAttributeSet();
	const FWidgetControllerParams Params(PC, PlayerState, ASC, AS);
	return AuraHUD->GetOverlayWidgetController(Params);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* const PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC))
	{
		return nullptr;
	}

	AAuraHUD* const AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!IsValid(AuraHUD))
	{
		return nullptr;
	}

	AAuraPlayerState* const PlayerState = PC->GetPlayerState<AAuraPlayerState>();
	if (!IsValid(PlayerState))
	{
		return nullptr;
	}

	UAbilitySystemComponent* const ASC = PlayerState->GetAbilitySystemComponent();
	UAttributeSet* const AS = PlayerState->GetAttributeSet();
	const FWidgetControllerParams Params(PC, PlayerState, ASC, AS);
	return AuraHUD->GeAttributeMenuWidgetController(Params);
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AAuraGameModeBase* const AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!IsValid(AuraGameMode))
	{
		return;
	}

	UCharacterClassInfo* ClassInfo = AuraGameMode->CharacterClassInfo;
	if (!IsValid(ClassInfo))
	{
		return;
	}

	AActor* const AvatarActor = ASC->GetAvatarActor();

	FCharactertClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryEffectContext = ASC->MakeEffectContext();
	PrimaryEffectContext.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle PrimaryEffectSpec = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryEffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryEffectSpec.Data.Get());

	FGameplayEffectContextHandle SecondaryEffectContext = ASC->MakeEffectContext();
	SecondaryEffectContext.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle SecondaryEffectSpec = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes, Level, SecondaryEffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryEffectSpec.Data.Get());

	FGameplayEffectContextHandle VitalEffectContext = ASC->MakeEffectContext();
	VitalEffectContext.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle VitalEffectSpec = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, Level, VitalEffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalEffectSpec.Data.Get());
}
