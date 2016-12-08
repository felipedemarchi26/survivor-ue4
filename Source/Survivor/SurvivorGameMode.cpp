// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "SurvivorGameMode.h"
#include "MyCharacter.h"

ASurvivorGameMode::ASurvivorGameMode() {
	DefaultPawnClass = AMyCharacter::StaticClass();
}


