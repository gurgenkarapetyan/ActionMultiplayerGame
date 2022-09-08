// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


USBTService_CheckHealth::USBTService_CheckHealth()
{
	LowHealthFraction = 0.3f;
}

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (APawn* const AIPawn = OwnerComp.GetAIOwner()->GetPawn(); ensure(AIPawn))
	{
		if (const USAttributeComponent* const AttributeComponent = USAttributeComponent::GetAttributes(AIPawn); ensure(AttributeComponent))
		{
			const bool bLowHealth = (AttributeComponent->GetHealth() / AttributeComponent->GetHealthMax()) < LowHealthFraction;

			UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
			BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		}
	}
}
