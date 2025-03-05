// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnvQueryContext_Player.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/Actor.h"
#include "AISystem.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Aura/Public/Characters/AuraCharacter.h"
#include "EngineUtils.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	TArray<AActor*> PlayerActors;
	for (TActorIterator<AActor> It(GetWorld(), AAuraCharacter::StaticClass()); It; ++It)
	{
		PlayerActors.Add(*It);
	}
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerActors);
}
