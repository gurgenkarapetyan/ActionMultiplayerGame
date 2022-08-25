// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSee);
}

void ASAICharacter::OnPawnSee(APawn* Pawn)
{
	AAIController* const AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BlackboardComponent = AIC->GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("TargetActor", Pawn);
	}
}
