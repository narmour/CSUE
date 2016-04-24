// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUEGameManager.h"


// Sets default values
ACSUEGameManager::ACSUEGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACSUEGameManager::BeginPlay()
{
	Super::BeginPlay();
    
    
	
}

// Called every frame
void ACSUEGameManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACSUEGameManager::initTeams(){
    ctAlive = ctTeam.Num();
    tAlive = tTeam.Num();
}

void ACSUEGameManager::killT(){
    tAlive-=1;
    
    if(tAlive)
}

