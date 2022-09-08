// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_Action.h"
#include "SActionComponent.h"
#include "SAction.h"


void ASPowerup_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	// Make sure we have instigator & that action class was set up
	if (!ensure(InstigatorPawn && ActionToGrant))
	{
		return;
	}

	// Check if Player already has action class
	if (USActionComponent* const ActionComponent = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if (ActionComponent->GetAction(ActionToGrant))
		{
			//UE_LOG(LogTemp, Log, TEXT("Instigator already has action of class: %s"), *GetNameSafe(ActionToGrant));
			const FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToGrant));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			return;
		}

		// Give new Ability
		ActionComponent->AddAction(InstigatorPawn, ActionToGrant);	
		HideAndCooldownPowerup();
	}
}
