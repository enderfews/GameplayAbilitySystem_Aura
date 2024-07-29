// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



USTRUCT(BlueprintType)
struct AURA_API FEffectPropertyContainer
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UAbilitySystemComponent* ASC;
	UPROPERTY()
	AActor* AvatarActor;
	UPROPERTY()
	AController* Controller;
	UPROPERTY()
	ACharacter* Character;
};

USTRUCT(BlueprintType)
struct AURA_API FEffectProperties
{
	GENERATED_BODY()

public:
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	FEffectPropertyContainer Source;
	UPROPERTY()
	FEffectPropertyContainer Target;
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

#pragma region Primary_Attributes

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

#pragma endregion

#pragma region Vital_Attributes

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

#pragma endregion

private:

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& oldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& oldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& oldVigor) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const;


	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
