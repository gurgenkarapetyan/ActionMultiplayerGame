// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


USBTService_CheckAttackRange::USBTService_CheckAttackRange()
{
	MaxAttackRange = 2000.f;
}

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between ai pawn and target actor
	if (UBlackboardComponent* const BlackBoardComp = OwnerComp.GetBlackboardComponent(); ensure(BlackBoardComp))
	{
		if (const AActor* const TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor")))
		{
			const AAIController* const MyController = OwnerComp.GetAIOwner();

			if (const APawn* const AIPawn = MyController->GetPawn(); ensure(AIPawn))
			{
				const float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

				const bool bWithinRange = DistanceTo < MaxAttackRange;

				bool bHasLOS = false;
				if (bWithinRange)
				{
					bHasLOS = MyController->LineOfSightTo(TargetActor);
				}

				BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
			}
		}
	}
}
