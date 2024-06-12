// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);

	void InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);
protected:

	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
};
