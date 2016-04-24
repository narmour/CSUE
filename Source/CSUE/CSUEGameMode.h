// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "CSUEGameManager.h"
#include "CSUEGameMode.generated.h"

UCLASS(minimalapi)
class ACSUEGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACSUEGameMode();

	//GameManager will call these functions
	void startRound();
	void endRound();
    
    virtual void BeginPlay() override;


	//HUD    will eventually get to this
    
private:
    UPROPERTY(EditAnywhere)
    ACSUEGameManager *myManager;
    
    int32 totalRoundsPlayed = 0;
};



