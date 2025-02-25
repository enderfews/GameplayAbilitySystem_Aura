// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_FindNearestPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIController* const AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(AIController))
	{
		return;
	}

	APawn* const ControlledPawn = AIController->GetPawn();
	if (!IsValid(ControlledPawn))
	{
		return;
	}

	if (!TargetTag.IsValid() || TargetTag.IsNone())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(this, TargetTag, FoundActors);
	FVector PawnLocation;
	float Distance;
	GetPawnLocation(OwnerComp, PawnLocation);
	AActor* const ClosestActor = GetClosestActorFromLocation(OwnerComp, FoundActors, PawnLocation, Distance);
	Blackboard->SetValue<UBlackboardKeyType_Object>(TargetKey.GetSelectedKeyID(), ClosestActor);
	Blackboard->SetValue<UBlackboardKeyType_Float>(DistanceKey.GetSelectedKeyID(), Distance);
}

void UBTService_FindNearestPlayer::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		PawnKey.ResolveSelectedKey(*BBAsset);
		TargetKey.ResolveSelectedKey(*BBAsset);
		DistanceKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_FindNearestPlayer::GetPawnLocation(UBehaviorTreeComponent& OwnerComp, FVector& outLocation)
{
	UBlackboardComponent* const BBComponent = OwnerComp.GetBlackboardComponent();
	if (PawnKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		AActor* Actor = Cast<AActor>(BBComponent->GetValue<UBlackboardKeyType_Object>(PawnKey.GetSelectedKeyID()));
		outLocation = Actor->GetActorLocation();
		return;
	}
	else if (PawnKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		outLocation = BBComponent->GetValue<UBlackboardKeyType_Vector>(PawnKey.GetSelectedKeyID());
		return;
	}
	
	outLocation = FAISystem::InvalidLocation;
}

AActor* UBTService_FindNearestPlayer::GetClosestActorFromLocation(UBehaviorTreeComponent& OwnerComp, const TArray<AActor*>& Actors, const FVector& Location, float& outDistance)
{
	float ClosestDistance = 9999999999999999.f;
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : Actors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		const FVector ActorLocation = Actor->GetActorLocation();
		const float Distance = (ActorLocation - Location).Size();
		if (ClosestActor == nullptr || Distance < ClosestDistance)
		{
			ClosestActor = Actor;
			ClosestDistance = Distance;
		}
	}
	outDistance = ClosestDistance;
	return ClosestActor;
}
