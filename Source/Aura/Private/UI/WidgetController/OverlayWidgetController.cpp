// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* const AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChangedSignature.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangedSignature.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangedSignature.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* const AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaChanged);
}

void UOverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChangedSignature.Broadcast(Data.NewValue);
}
