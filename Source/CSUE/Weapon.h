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
    //constructor that takes in damage. for the child classes
    AWeapon(float wDamage);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;
    
    float weaponRange;
    float weaponDamage;
    
    //Function to shoot a bullet and check what it hits
    void WeaponTrace();
    
    APawn *myPawn;
	
protected:

   
	
};
