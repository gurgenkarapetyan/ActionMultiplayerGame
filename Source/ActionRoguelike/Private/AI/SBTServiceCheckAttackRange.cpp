// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTServiceCheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTServiceCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AI Pawn and Target Actor
	UBlackboardComponent* const BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AActor* const TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			const AAIController* const AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				const APawn* const AIPawn = AIController->GetPawn();
				if (ensure(AIPawn))
				{
					const float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					const bool bWithThisRange = DistanceTo < 2000.f;

					bool bHasLineOfSight = false;
					if (bWithThisRange)
					{
						bHasLineOfSight = AIController->LineOfSightTo(TargetActor);
					}
					
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithThisRange);
				}
			}
		}
	}
}
