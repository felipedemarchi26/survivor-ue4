// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "MyCharacter.h"
#include "Shoot.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));
	MeshComp->SetWorldScale3D(FVector(1.25f, 1.25f, 1.85f));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(GetCapsuleComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>
		(TEXT("CameraComp"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->SetWorldRotation(FRotator(-40.0f, 0.0f, 0.0f));

	CameraComp->SetupAttachment(CameraBoom);
	CameraBoom->SetupAttachment(GetCapsuleComponent());

	ArrowComp = CreateDefaultSubobject<UArrowComponent>
		(TEXT("ArrowComp"));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->SetCollisionProfileName("NoCollision");
	ArrowComp->SetupAttachment(MeshComp);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Life = 3;
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Forward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("Side", this, &AMyCharacter::MoveSide);
	InputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
}

void AMyCharacter::MoveForward(float Val) {
	if (Controller != nullptr && Val != 0) {
		FRotator Rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround()) {
			Rotation.Pitch = 0.0f;
		}
		const FVector Direction = FRotationMatrix(Rotation).
			GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void AMyCharacter::MoveSide(float Val) {
	if (Controller != nullptr && Val != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).
			GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

void AMyCharacter::Turn(float Val) {
	FRotator Rotation = MeshComp->GetComponentRotation();
	Rotation.Yaw += Val;
	MeshComp->SetWorldRotation(Rotation);
}

void AMyCharacter::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void AMyCharacter::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AMyCharacter::Fire() {
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();
	if (World != nullptr) {
		FRotator Rotation = MeshComp->GetComponentRotation();
		World->SpawnActor<AShoot>(GetActorLocation(), Rotation,
			SpawnParameters);
	}
}