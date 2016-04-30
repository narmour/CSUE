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
    
protected:
    UPROPERTY(EditAnywhere)
    
    TSubclassOf<ACSUEGameManager> managerClass;
    
    ACSUEGameManager *myManager;
    
    int32 totalRoundsPlayed = 0;
    
    //widget class for hud
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TSubclassOf<UUserWidget> HUDWidgetClass;
    
    //instance of hud
    UPROPERTY()
    UUserWidget *CurrentWidget;
    
    
};



