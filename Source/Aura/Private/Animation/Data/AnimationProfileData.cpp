// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Data/AnimationProfileData.h"
#include "Identity/Interfaces/IdentityTagAssetInterface.h"


UAnimMontage* UAnimationProfileData::GetAnimationMontageFromTag(const FGameplayTag& AnimationContextTag, AActor* ActorContext)
{
	//TODO: Add debug logs so that It's easier to tackle bugs ;)
	if (!IsValid(ActorContext))
	{
		return nullptr;
	}

	if (!AnimationContextTag.IsValid())
	{
		return nullptr;
	}

	if (!ActorContext->Implements<UIdentityTagAssetInterface>())
	{
		return nullptr;
	}

	if (!AnimationProfiles.Contains(AnimationContextTag))
	{
		return nullptr;
	}

	FGameplayTag ActorIdentityTag;
	IIdentityTagAssetInterface::Execute_GetCharacterTag(ActorContext, ActorIdentityTag);

	if (!ActorIdentityTag.IsValid())
	{
		return nullptr;
	}

	const FAnimationCharacterProfileContainer& AnimationProfileContainer = AnimationProfiles[AnimationContextTag];
	if (!AnimationProfileContainer.CharacterProfiles.Contains(ActorIdentityTag))
	{
		return nullptr;
	}

	UAnimationProfileHandler* const AnimationProfileHandler = AnimationProfileContainer.CharacterProfiles[ActorIdentityTag];
	if (!IsValid(AnimationProfileHandler))
	{
		return nullptr;
	}

	return AnimationProfileHandler->GetMontageForContext(ActorContext);
}
