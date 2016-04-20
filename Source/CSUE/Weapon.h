// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "CSUEAIEnemyCharacter.cpp"
#include "Weapon.generated.h"

UCLASS()

class CSUE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    AWeapon();
    //constructor for child classes
	AWeapon(float wR,float wD,float wFR);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;
    
    UPROPERTY(EditDefaultsOnly,Category = "Sound")
    USoundCue *FireLoopSound;
    
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue *FireFinishSound;
    
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem *MuzzleFX;
    
    UPROPERTY(EditDefaultsOnly,Category = "Effects")
    UParticleSystem *HitFX;
    
    float weaponRange;
    float weaponDamage;
    float weaponFireRate;
    
    //Functions to shoot a bullet and check what it hits
    void OnStartFire();
    void OnStopFire();
    void WeaponTrace();
    FTimerHandle shootingTimer;
    
    APawn *myPawn;
	
protected:
    //function to use audio/muzzle flash
    UAudioComponent *PlayWeaponSound(USoundCue *Sound);
    UParticleSystemComponent *muzzleFlash(UParticleSystem *particle);
    
    
    UPROPERTY(Transient)
    UAudioComponent *ShootAC;
    
    UPROPERTY(Transient)
    UParticleSystemComponent *muzzlePSC;

   
	
};
