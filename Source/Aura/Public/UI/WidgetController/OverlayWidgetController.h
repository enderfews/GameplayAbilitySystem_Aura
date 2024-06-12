// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attribues")
	FOnHealthChangedSignature OnHealthChangedSignature;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attribues")
	FOnMaxHealthChangedSignature OnMaxHealthChangedSignature;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attribues")
	FOnManaChangedSignature OnManaChangedSignature;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attribues")
	FOnMaxManaChangedSignature OnMaxManaChangedSignature;

protected:
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	void OnManaChanged(const FOnAttributeChangeData& Data);
	void OnMaxManaChanged(const FOnAttributeChangeData& Data);
};
