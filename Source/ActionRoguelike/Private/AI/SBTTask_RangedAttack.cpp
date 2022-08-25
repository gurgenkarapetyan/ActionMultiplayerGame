// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		const ACharacter* const CharacterPawn = Cast<ACharacter>(AIController->GetPawn());
		if (CharacterPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		const AActor* const TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		const FVector MuzzleLocation = CharacterPawn->GetMesh()->GetSocketLocation("Muzzle_01");
		const FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		const FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const AActor* const NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);
		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
