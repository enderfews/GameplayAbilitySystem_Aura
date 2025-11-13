// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AuraSettings.generated.h"

/**
 * The class setting for all settings related to the project (debug flags, global variables, references, etc)
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Aura Settings"))
class AURA_API UAuraSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	//Reference to the data asset that contains all animation profiles
	UPROPERTY(config, EditAnywhere, Category = "Animation|Profiles", meta = (AllowedClasses = "AnimationProfileData"))
	FSoftObjectPath AnimationBank;

	static UAuraSettings* Get() { return GetMutableDefault<UAuraSettings>(); }
};

UCLASS()
class AURA_API UAuraSettingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UAuraSettings* GetAuraSettings()
	{
		return UAuraSettings::Get();
	}
};
