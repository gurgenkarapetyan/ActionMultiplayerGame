// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.f;
}

bool USAttributeComponent::ApplyHealthChange(AActor* Instigator, float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);
	
	return true;
}

bool USAttributeComponent::IsAlive()
{
	return Health > 0.f;
}

USAttributeComponent* USAttributeComponent::GetAttributes(const AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(const AActor* Actor)
{
	if (USAttributeComponent* const AttributeComponent = GetAttributes(Actor))
	{
		return AttributeComponent->IsAlive();
	}

	return false;
}
