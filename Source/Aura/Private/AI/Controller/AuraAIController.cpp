// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AuraAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/AuraAITypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"


AAuraAIController::AAuraAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));


}

AActor* AAuraAIController::GetCombatTarget_Implementation() const
{
	return Cast<AActor>(BlackboardComponent->GetValueAsObject(FBlackboard::KeyTargetToFollow));
}

FVector AAuraAIController::GetCombatTargetLocation_Implementation() const
{
	AActor* const Target = ICombatTargeting::Execute_GetCombatTarget(this);
	if (IsValid(Target))
	{
		return Target->GetActorLocation();
	}
	return FAISystem::InvalidLocation;
}

void AAuraAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const uint8 CharacterRole = static_cast<uint8>(ICombatInterface::Execute_GetCharacterClass(InPawn));
	BlackboardComponent->SetValueAsBool(FBlackboard::KeyHitReacting, false);
	BlackboardComponent->SetValueAsEnum(FBlackboard::KeyCharacterRole, CharacterRole);
	UAbilitySystemComponent* const ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InPawn);
	if (!IsValid(ASC))
	{
		return;
	}

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	ASC->RegisterGameplayTagEvent(GameplayTags.Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AAuraAIController::OnHitReactChanged
	);
}

void AAuraAIController::OnHitReactChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	const bool PrevHitReacting = BlackboardComponent->GetValueAsBool(FBlackboard::KeyHitReacting);
	const bool CurrentHitReacting = NewCount > 0;
	if (CurrentHitReacting != PrevHitReacting)
	{
		BlackboardComponent->SetValueAsBool(FBlackboard::KeyHitReacting, CurrentHitReacting);
	}

}
