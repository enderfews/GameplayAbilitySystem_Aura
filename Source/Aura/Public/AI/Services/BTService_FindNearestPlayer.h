// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindNearestPlayer.generated.h"

/**
 * Find nearest player
 */
UCLASS()
class AURA_API UBTService_FindNearestPlayer : public UBTService
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Node)
	FName TargetTag; //TODO: Change it to use FGameplayTag
	UPROPERTY(EditAnywhere, Category = Node)
	FBlackboardKeySelector TargetKey;
	UPROPERTY(EditAnywhere, Category = Node)
	FBlackboardKeySelector PawnKey;
	UPROPERTY(EditAnywhere, Category = Node)
	FBlackboardKeySelector DistanceKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

private:
	void GetPawnLocation(UBehaviorTreeComponent& OwnerComp, FVector& outLocation);
	AActor* GetClosestActorFromLocation(UBehaviorTreeComponent& OwnerComp, const TArray<AActor*>& Actors,const FVector& Location, float& outDistance);
};
