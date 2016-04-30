// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUECharacter.h"
#include "CSUEAICharacter.h"
#include "Weapon.h"
#include "CSUETerrorist.h"
#include "CSUECounterTerrorist.h"




//default construct
AWeapon::AWeapon(){
    PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("base CLASS"));
    RootComponent = WeaponMesh;
    
    //init shooting audio loop
    ShootAC = nullptr;

    weaponRange = 9999.f;
    weaponDamage = 1.f;
    weaponFireRate = .05f;
}


// Sets values for child classes
AWeapon::AWeapon(float wR,float wD,float wFR)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("base CLASS"));
    RootComponent = WeaponMesh;
    
    //init shooting audio loop
    ShootAC = nullptr;
    
    
    //weapon stats
    weaponRange = wR;
    weaponDamage = wD;
    weaponFireRate = wFR;
    
    
}


// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
    auto playerChar = Cast<ACSUECharacter>(myPawn);
    //check if the weapon is equiped by player char, if not, get enemy type from AICHAR
    if(playerChar)
        enemyType =playerChar->getEnemyTeam();
    else{
        auto aiChar = Cast<ACSUEAICharacter>(myPawn);
        enemyType = aiChar->getEnemyTeam();
        //pure virtual works, doope
        UE_LOG(LogTemp,Warning,TEXT("%s"),*enemyType);
    }

	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue *Sound){
    UAudioComponent *AC = NULL;
    
    if (Sound) {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    return AC;
}

UParticleSystemComponent * AWeapon::muzzleFlash(UParticleSystem * particle)
{
    UParticleSystemComponent *flash = NULL;
    
    if (particle) {
        flash = UGameplayStatics::SpawnEmitterAttached(particle,RootComponent,TEXT("MuzzleFlashSocket"));
        
    }
    return flash;
}

void AWeapon::OnStartFire()
{
    ShootAC = PlayWeaponSound(FireLoopSound);
    muzzlePSC = muzzleFlash(MuzzleFX);
    GetWorldTimerManager().SetTimer(shootingTimer,this,&AWeapon::WeaponTrace,weaponFireRate,true);

    WeaponTrace();
    
}

void AWeapon::OnStopFire()
{
    GetWorldTimerManager().ClearTimer(shootingTimer);
    ShootAC->Deactivate();
    muzzlePSC->DeactivateSystem();
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
	//spray patterns?
    FVector endPos = forward.GetSafeNormal() * weaponRange;
    
    
    //check if we blasted an enemy wit our weapon
    FCollisionQueryParams traceParams(FName(TEXT("WeaponTrace")), true,Instigator);
    traceParams.bTraceAsyncScene = true;
    traceParams.bReturnPhysicalMaterial = true;
    
    //check our fire ray against all objects with collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, startPos, endPos, FCollisionObjectQueryParams::AllObjects, traceParams);
    if(Hit.bBlockingHit){
        //spawn hit effect particle
		if (Hit.GetActor()) {
			UGameplayStatics::SpawnEmitterAtLocation(Hit.GetActor(), HitFX, Hit.ImpactPoint);
            //if we hit an enemy, deal damage
            auto hitEnemy = Cast<ACSUEAICharacter>(Hit.GetActor());
            if(hitEnemy && enemyType != hitEnemy->getEnemyTeam()){
                hitEnemy->takeDamage(weaponDamage);
            }
            
        }
        
    }
    
}

