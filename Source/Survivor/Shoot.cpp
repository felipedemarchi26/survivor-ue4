// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "Shoot.h"
#include "Enemy.h"
#include "MyCharacter.h"


// Sets default values
AShoot::AShoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USphereComponent>
		(TEXT("Root"));
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	Root->bGenerateOverlapEvents = true;
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->OnComponentBeginOverlap.AddDynamic(
	this, &AShoot::OnOverlapBegin);

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject
		<UProjectileMovementComponent>(TEXT("ProjMov"));
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->UpdatedComponent = Root;

	InitialLifeSpan = 4.0f;
}

// Called when the game starts or when spawned
void AShoot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShoot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AShoot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && 
		OtherActor->IsA(AEnemy::StaticClass())) {

		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy) {
			Enemy->SetLife(Enemy->GetLife() - 1);
			UE_LOG(LogTemp, Warning, TEXT("Retirou vida"));
			if (Enemy->IsDead()) {
				Enemy->Destroy();
				AMyCharacter* Player = Cast<AMyCharacter>
					(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
				Player->SetPontuacao(Player->GetPontuacao() + 10);
				UE_LOG(LogTemp, Warning, TEXT("%d"), Player->GetPontuacao());
			}
			Destroy();
		}

	}
}
