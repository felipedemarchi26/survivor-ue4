// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();
	virtual void Possess(APawn* Pawn) override;
	uint8 EnemyKeyID;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const 
	{ return BlackboardComp; }

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const
	{ return BehaviorComp; }

private:
	UBlackboardComponent* BlackboardComp;
	UBehaviorTreeComponent* BehaviorComp;
	
	
};
