// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CSUE.h"
#include "CSUEGameMode.h"
#include "CSUEHUD.h"
#include "CSUECharacter.h"

ACSUEGameMode::ACSUEGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACSUEHUD::StaticClass();

}

void ACSUEGameMode::BeginPlay(){
    UE_LOG(LogTemp, Warning, TEXT("HI FROM GAMEMODE BEGINPLAY"));
    startRound();

}

void ACSUEGameMode::startRound(){
    totalRoundsPlayed +=1;
    
   // myManager->
    
}
