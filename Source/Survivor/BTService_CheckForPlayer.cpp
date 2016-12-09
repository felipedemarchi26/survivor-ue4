// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MyAIController.h"
#include "MyCharacter.h"

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds) {

	AMyAIController* EnemyPC = Cast<AMyAIController>
		(OwnerComp.GetAIOwner());

	if (EnemyPC) {
		UWorld* World = GetWorld();
		if (World) {
			AMyCharacter* Player = Cast<AMyCharacter>
				(World->GetFirstPlayerController()->GetPawn());

			if (Player) {
				OwnerComp.GetBlackboardComponent()->SetValue
					<UBlackboardKeyType_Object>
					(EnemyPC->EnemyKeyID, Player);
				UE_LOG(LogTemp, Warning, TEXT("Player encontrado!"));
			}
		}
	}

}


