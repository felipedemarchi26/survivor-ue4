// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class SURVIVOR_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	FORCEINLINE int GetPontuacao() const { return Pontuacao; }
	FORCEINLINE void AMyCharacter::SetPontuacao(int NewPontuacao)
	{ Pontuacao = NewPontuacao; }
	FORCEINLINE int GetLife() const { return Life; }
	FORCEINLINE void AMyCharacter::SetLife(int NewLife)
	{Life = NewLife;}

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	int Pontuacao;
	UPROPERTY(EditAnywhere)
	int Life;

	void MoveForward(float Val);
	void MoveSide(float Val);
	void Turn(float Val);
	void StartRun();
	void StopRun();
	void Fire();
	
};
