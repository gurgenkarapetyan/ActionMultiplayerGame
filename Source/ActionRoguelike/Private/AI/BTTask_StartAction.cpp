// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_StartAction.h"
#include "AIController.h"
#include "SActionComponent.h"


EBTNodeResult::Type UBTTask_StartAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* MyController = OwnerComp.GetAIOwner(); ensure(MyController))
	{
		APawn* MyPawn = MyController->GetPawn();
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		if (USActionComponent* ActionComponent = Cast<USActionComponent>(MyPawn->GetComponentByClass(USActionComponent::StaticClass())); ensure(ActionComponent))
		{
			if (ActionComponent->StartActionByName(MyPawn, ActionName))
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
