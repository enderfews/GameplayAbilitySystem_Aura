// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTasks/BTTask_ActivateGameplayAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


UBTTask_ActivateGameplayAbility::UBTTask_ActivateGameplayAbility(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
	NodeName = "Activate Gameplay Ability";
	// Accept only actors
	ActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_ActivateGameplayAbility, ActorKey), AActor::StaticClass());
	ActorKey.SelectedKeyName = FBlackboard::KeySelf;
}

EBTNodeResult::Type UBTTask_ActivateGameplayAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AbilityTags.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		return EBTNodeResult::Failed;
	}
	
	AActor* const TargetActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(ActorKey.GetSelectedKeyID()));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* const ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(ASC))
	{
		return EBTNodeResult::Failed;
	}

	ASC->TryActivateAbilitiesByTag(AbilityTags);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_ActivateGameplayAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UBTTask_ActivateGameplayAbility::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		ActorKey.ResolveSelectedKey(*BBAsset);
	}
}
