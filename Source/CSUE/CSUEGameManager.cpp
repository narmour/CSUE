// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUEGameMode.h"
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
    
    UE_LOG(LogTemp,Warning,TEXT("HI FROM BEGINPLAY"));
    //find spawn points in world and put them in respective arrays
    
    for(TActorIterator<ATargetPoint> targetItr(GetWorld());targetItr;++targetItr){
        auto tPoint = *targetItr;
        
        //if its a ct spawn point, put in ct array, else put in t array
        if(tPoint->GetName().Contains(FString(TEXT("ct")))){
            ctSpawns.Add(tPoint);
            
        }
        else{
            tSpawns.Add(tPoint);
        }
    }
    UE_LOG(LogTemp,Warning,TEXT("BEGINPLAY  T: %i    CT:%i "),tSpawns.Num(),ctSpawns.Num());
    

    auto myGM = (ACSUEGameMode*)GetWorld()->GetAuthGameMode();
    if(myGM)
        myGM->startRound();
    //initTeams();
    
    
    
	
}

// Called every frame
void ACSUEGameManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACSUEGameManager::initTeams(){
    //if we set spawn points spawn 5 CT and 5 T
    UWorld* World = GetWorld();
    //UE_LOG(LogTemp,Warning,TEXT("TRIED TO SPAWN  T: %i    CT:%i "),tSpawns.Num(),ctSpawns.Num());
    //tTeam.Empty();
    //ctTeam.Empty();
    if(tSpawns.Num() ==5 && ctSpawns.Num() == 5){

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            FRotator Rotation(0.f,180.f,0.f);
        for(int i =0;i<tSpawns.Num();i++){
            FVector spawnLoc = tSpawns[i]->GetActorLocation();
            //spawn terrorist team
            auto terrorist = World->SpawnActor<ACSUETerrorist>(tClass,spawnLoc,Rotation,SpawnParams);
            tTeam.Add(terrorist);
            //attach ai controller here??
            
            spawnLoc = ctSpawns[i]->GetActorLocation();
            //spawn ct team
            auto counterTerrorist = World->SpawnActor<ACSUECounterTerrorist>(ctClass,spawnLoc,FRotator::ZeroRotator,SpawnParams);
            ctTeam.Add(counterTerrorist);
            
            
        }
        
        
        
    }
    ctAlive = ctTeam.Num();
    tAlive = tTeam.Num();
}

void ACSUEGameManager::killT(){
    tAlive-=1;
    UE_LOG(LogTemp,Warning,TEXT("KILLED T"));
    //if(tAlive)
    if(tAlive ==0){
        auto myGM = (ACSUEGameMode*)GetWorld()->GetAuthGameMode();
        myGM->endRound(FString(TEXT("ct")));
    }
}

void ACSUEGameManager::killCT(){
    ctAlive-=1;
    UE_LOG(LogTemp,Warning,TEXT("KILLED CT"));
    if (ctAlive ==0){
        auto myGM = (ACSUEGameMode*)GetWorld()->GetAuthGameMode();
        myGM->endRound(FString(TEXT("t")));
    }

}
