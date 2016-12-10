// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "SpawnEnemy.h"
#include "Enemy.h"
#include "MyAIController.h"


// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("NoCollision");
	RootComponent = Root;

	ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBlue
	(TEXT("Blueprint'/Game/Blueprints/EnemyBP.EnemyBP'"));
	if (EnemyBlue.Succeeded()) {
		EnemyBP = (UClass*)EnemyBlue.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(CountdownTimerHandle,
		this, &ASpawnEnemy::TimerManager, 1.0f, true);

	CountdownTimer = FMath::FRandRange(1.0f, 20.0f);
}

// Called every frame
void ASpawnEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawnEnemy::TimerManager() {
	CountdownTimer -= 1.0f;
	if (CountdownTimer <= 0.0f) {
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParamenters;
			AEnemy* Enemy = World->SpawnActor<AEnemy>
				(EnemyBP, GetActorLocation(), FRotator::ZeroRotator,
					SpawnParamenters);

			AMyAIController* AIControl = World->SpawnActor
				<AMyAIController>(GetActorLocation(), FRotator::ZeroRotator,
					SpawnParamenters);

			AIControl->Possess(Enemy);
			CountdownTimer = FMath::FRandRange(1.0f, 20.0f);
		}
	}
}