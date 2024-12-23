// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfigDataAsset.h"
#include "Algo/Find.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfigDataAsset::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	const FAuraInputAction* const FoundAbilityInputAction = Algo::FindByPredicate(AbilityInputActions, [&InputTag](const FAuraInputAction& Info)
		{
			return IsValid(Info.InputAction) && Info.InputTag.MatchesTagExact(InputTag);
		});

	if (FoundAbilityInputAction)
	{
		return FoundAbilityInputAction->InputAction;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find input action for input tag [%s] on [%s]"), *InputTag.ToString(), TEXT("__FUNCTION__"));
	}
	return nullptr;
}
