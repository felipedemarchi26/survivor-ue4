// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MyAIController.h"
#include "MyCharacter.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	AMyAIController* EnemyPC = Cast<AMyAIController>
		(OwnerComp.GetAIOwner());

	if (EnemyPC) {
		AMyCharacter* Player = Cast<AMyCharacter>
			(OwnerComp.GetBlackboardComponent()->GetValue
			<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID));
		
		if (Player) {

			EnemyPC->MoveToActor(Player, -1.0f, true, true, true, 0, true);

			return EBTNodeResult::Succeeded;

		}
	}
	return EBTNodeResult::Failed;

}


