// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfigDataAsset.h"
#include "AuraInputComponent.generated.h"



/*
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const  UAuraInputConfigDataAsset* InputConfig
		, UserClass* Object
		, PressedFuncType PressedFunc
		, ReleasedFuncType ReleasedFunc
		, HeldFuncType HeldFunc)
	{
		check(InputConfig);

		for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
		{
			if (!IsValid(Action.InputAction) || !Action.InputTag.IsValid())
			{
				continue;
			}

			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
};
