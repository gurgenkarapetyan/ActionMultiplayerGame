// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealSelf.h"
#include "SAttributeComponent.h"
#include "AIController.h"


EBTNodeResult::Type USBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	USAttributeComponent* const AttributeComponent = USAttributeComponent::GetAttributes(MyPawn);
	if (ensure(AttributeComponent))
	{
		AttributeComponent->ApplyHealthChange(MyPawn, AttributeComponent->GetHealthMax());
	}

	return EBTNodeResult::Succeeded;
}
