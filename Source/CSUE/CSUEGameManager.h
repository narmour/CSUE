// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CSUETerrorist.h"
#include "CSUECounterTerrorist.h"
#include "CSUEGameManager.generated.h"

UCLASS()
class CSUE_API ACSUEGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSUEGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    //sets tAlive and ctAlive, called at the start of every round
    void initTeams();
    
    //decrement tAlive/ctAlive check for round end, called by Terrorist/CT classes.
    void killT();
    void killCT();


private:
	//T AND CT TEAMS
    UPROPERTY(EditAnywhere,Category ="Teams")
    TArray<ACSUETerrorist*> tTeam;
    UPROPERTY(EditAnywhere,Category ="Teams")
    TArray<ACSUECounterTerrorist*> ctTeam;
    
    //Keeps track of num alive for each team.
    int32 tAlive;
    int32 ctAlive;

	
	
};
