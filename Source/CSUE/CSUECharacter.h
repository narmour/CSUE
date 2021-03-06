// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "CSUERifle.h"
#include "CSUEShotgun.h"
#include "CSUECharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ACSUECharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//class USkeletalMeshComponent* FP_Gun;


	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
    
    //give char our weapon class
    UPROPERTY(EditAnywhere,Category = "Weapon")
    TSubclassOf<AWeapon> RifleClass;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon> ShotgunClass;

	//Team character is on, hardcoded for CT, want to set with HUD?
    FString myTeam = FString(TEXT("T"));
   
	
	void switchWeapon();
    
    virtual void BeginPlay() override;
    
public:
	ACSUECharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ACSUEProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;
    
    //function to return enemy type so weapon knows who the bad guys are
	UFUNCTION(BlueprintCallable, Category = "Team")
    FString getEnemyTeam();
    
    UPROPERTY(EditAnywhere)
    int32 charHealth;
    
    UFUNCTION(BlueprintPure,Category = "player")
    int32 getHealth() const;
	//rifle is default starting weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	FString currentWeapon = FString(TEXT("rifle"));

	//instance of the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		ACSUERifle *myRifle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		ACSUEShotgun *myShotgun;

    

protected:
	
	/** Fires a projectile. */
	void OnFire();
    void OnStopFire();
    bool bShooting;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
    
    
    
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

