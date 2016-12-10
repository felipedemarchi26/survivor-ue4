// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "Enemy.h"
#include "MyCharacter.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(GetCapsuleComponent());

	GetCapsuleComponent()->OnComponentHit.AddDynamic(
		this, &AEnemy::OnHit);

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Life = 3;
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool AEnemy::IsDead() {
	if (Life <= 0) {
		return true;
	}
	return false;
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit) {

	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyCharacter::StaticClass())) {

		AMyCharacter* Player = Cast<AMyCharacter>
			(OtherActor);
		if (Player) {
			Player->SetLife(Player->GetLife() - 1);
			Player->SetPontuacao(Player->GetPontuacao() - 50);
			Destroy();
		}

	}

}