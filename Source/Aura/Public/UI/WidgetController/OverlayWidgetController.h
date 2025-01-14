// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "OverlayWidgetController.generated.h"


class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AssetTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribues")
	FOnAttributeChangedSignature OnHealthChangedSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribues")
	FOnAttributeChangedSignature OnMaxHealthChangedSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribues")
	FOnAttributeChangedSignature OnManaChangedSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribues")
	FOnAttributeChangedSignature OnMaxManaChangedSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRow;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template<typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	if (!IsValid(DataTable) || !Tag.IsValid())
	{
		return nullptr;
	}

	return DataTable->FindRow<T>(Tag.GetTagName(), FString::Format(TEXT("{0} - Finding row tag"), {TEXT(__FUNCTION__)}));
}
