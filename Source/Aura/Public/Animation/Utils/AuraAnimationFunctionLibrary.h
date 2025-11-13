// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAnimationFunctionLibrary.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAnimationFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UAnimMontage* GetAnimationMontageFromTag(FGameplayTag AnimationContextTag, AActor* ActorContext);
};
