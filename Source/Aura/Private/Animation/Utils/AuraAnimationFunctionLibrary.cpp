// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Utils/AuraAnimationFunctionLibrary.h"
#include "Settings/AuraSettings.h"
#include "Animation/Data/AnimationProfileData.h"


UAnimMontage* UAuraAnimationFunctionLibrary::GetAnimationMontageFromTag(FGameplayTag AnimationContextTag, AActor* ActorContext)
{
	UAuraSettings* const AuraSettings = UAuraSettings::Get();
	UAnimationProfileData* AnimationProfileData = Cast<UAnimationProfileData>(AuraSettings->AnimationBank.ResolveObject());
	if (!IsValid(AnimationProfileData))
	{
		AnimationProfileData = Cast<UAnimationProfileData>(AuraSettings->AnimationBank.TryLoad());
	}
	return AnimationProfileData->GetAnimationMontageFromTag(AnimationContextTag, ActorContext);
}
