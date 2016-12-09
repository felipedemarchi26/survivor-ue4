// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Enemy.h"

AMyAIController::AMyAIController() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>
		(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>
		(TEXT("BehaviorComp"));
}

void AMyAIController::Possess(APawn* Pawn) {
	Super::Possess(Pawn);

	AEnemy* Enemy = Cast<AEnemy>(Pawn);

	if (Enemy && Enemy->BotBehavior) {
		BlackboardComp->InitializeBlackboard(
			*Enemy->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Enemy->BotBehavior);
	}
}



