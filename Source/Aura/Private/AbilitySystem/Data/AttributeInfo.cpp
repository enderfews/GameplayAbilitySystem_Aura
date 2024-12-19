// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"
#include "Algo/Find.h"

void UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, FAuraAttributeInfo& outAttributeInfo, bool bLogNotFound/* = false*/) const
{
	const FAuraAttributeInfo* FoundAttributeInfo = Algo::FindByPredicate(AttributeInformation, [&AttributeTag](const FAuraAttributeInfo& Info)
		{
			return Info.AttributeTag.MatchesTagExact(AttributeTag);
		});

	if (FoundAttributeInfo)
	{
		outAttributeInfo = *FoundAttributeInfo;
		return;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for attribute tag [%s] on [%s]"), *AttributeTag.ToString(), TEXT("__FUNCTION__"));
	}

	outAttributeInfo = FAuraAttributeInfo();
	return;
}
