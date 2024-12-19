// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

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
