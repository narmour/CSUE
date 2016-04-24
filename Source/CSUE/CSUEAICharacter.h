// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "CSUEAICharacter.generated.h"

UCLASS()
class CSUE_API ACSUEAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSUEAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	void takeDamage(float damage);


protected:
	//character health
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float myHealth;
    
    UPROPERTY(EditAnywhere,Category = "Weapon")
    TSubclassOf<AWeapon>weaponType;
    
    AWeapon *myWeapon;
    
    UPROPERTY(EditAnywhere, Category="Mesh")
    class USkeletalMeshComponent* Mesh3P;

	
	
};
