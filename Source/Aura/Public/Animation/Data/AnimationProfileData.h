// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AnimationProfileData.generated.h"

class UAnimMontage;

/**
 * Base class for Animation Profile Handlers. Used to retrieve the right animation
 * for a given context
 */
UCLASS(DefaultToInstanced, EditInlineNew, BlueprintType)
class AURA_API UAnimationProfileHandler : public UObject
{
	GENERATED_BODY()

protected:
	
	virtual UAnimMontage* GetMontageForContext(UObject* Context)
	{
		return nullptr;
	};

	friend class UAnimationProfileData;
};

/*
* Returns the animation set in the class. Simple
*/
UCLASS(DefaultToInstanced, EditInlineNew, BlueprintType)
class AURA_API UGetAnimationHandler : public UAnimationProfileHandler
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontage;
protected:

	virtual UAnimMontage* GetMontageForContext(UObject* Context)
	{
		return AnimMontage;
	};

	friend class UAnimationProfileData;
};

USTRUCT(BlueprintType)
struct FAnimationCharacterProfileContainer
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Animation Profile")
	TMap<FGameplayTag, UAnimationProfileHandler*> CharacterProfiles;
};

/*
* The animation bank where all animations are stored and defined for each character in different contexts.
* The key is the context (Ex: Animation.Melee) and the value is a container which contains all the animations
* from that context for each defined character. Ex (<Animation.Melee, <Character.Goblin.Spear, AnimMeleeGoblin>>).
* Animations are not stored directly but in an UObject called UAnimationProfileHandler, in charge of calculating the
* right animation for the given actor.
*/
UCLASS(Blueprintable, BlueprintType)
class AURA_API UAnimationProfileData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Animation Profile")
	TMap<FGameplayTag, FAnimationCharacterProfileContainer> AnimationProfiles;

	/*
	* Gets the right animation montage for an actor in a given context
	* @param AnimationContextTag - A gameplay tag which defines the context of the animation (Ex: Animation.Melee)
	* @param ActorContext - The actor we are retrieving the anim montage
	* @return UAnimMontage - The anim montage from the context. (Ex: Animation.Melee and a Goblin as context will return the melee animation for a goblin)
	*/
	UAnimMontage* GetAnimationMontageFromTag(const FGameplayTag& AnimationContextTag, AActor* ActorContext);
};
