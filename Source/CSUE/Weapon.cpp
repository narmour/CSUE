// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUEAIEnemyCharacter.h"
#include "CSUECharacter.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("base CLASS"));
    RootComponent = WeaponMesh;
    
    weaponRange = 999999.f;
    weaponDamage = 1.f;
}

AWeapon::AWeapon(float wDamage){
    weaponDamage = wDamage;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeapon::WeaponTrace(){
	//cast pawn to char
	auto myFPChar = Cast<ACSUECharacter>(myPawn);
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    
    FVector startPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
	FVector forward;
	if (myFPChar) {
		forward = myFPChar->GetFirstPersonCameraComponent()->GetForwardVector();
	}
    FVector endPos = forward.GetSafeNormal() * weaponRange;
    
    
    //check if we blasted an enemy wit our weapon
    FCollisionQueryParams traceParams(FName(TEXT("WeaponTrace")), true,Instigator);
    traceParams.bTraceAsyncScene = true;
    traceParams.bReturnPhysicalMaterial = true;
    
    //check our fire ray against all objects with collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, startPos, endPos, FCollisionObjectQueryParams::AllObjects, traceParams);
    
    if(Hit.bBlockingHit){
        auto hitEnemy = Cast<ACSUEAIEnemyCharacter>(Hit.GetActor());
        if(hitEnemy){
            UE_LOG(LogTemp,Warning,TEXT("HIT ENEMY"));
        }
        
    }
    
    
    
}

