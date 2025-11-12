// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interaction/CombatTargeting.h"
#include "AuraAIController.generated.h"


class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraAIController
	: public AAIController
	, public ICombatTargeting
{
	GENERATED_BODY()
	
public:

	AAuraAIController();

#pragma region ICombatTargeting

	virtual AActor* GetCombatTarget_Implementation() const override;
	virtual FVector GetCombatTargetLocation_Implementation() const override;

#pragma endregion

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UFUNCTION()
	void OnHitReactChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
