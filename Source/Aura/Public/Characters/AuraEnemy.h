// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy
	: public AAuraCharacterBase
	, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	AAuraEnemy();
#pragma region IEnemyInterface
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
#pragma endregion

#pragma region ICombatInterface
	virtual int32 GetLevel() const override;
#pragma endregion

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
