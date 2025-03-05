// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"
#include "BTTask_ActivateGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UBTTask_ActivateGameplayAbility : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Node)
	FGameplayTagContainer AbilityTags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Node)
	FBlackboardKeySelector ActorKey;
	UBTTask_ActivateGameplayAbility(const FObjectInitializer& Initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
};
