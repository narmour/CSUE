// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUERifle.h"




void ACSUERifle::OnStartFire()
{
	
		UE_LOG(LogTemp, Warning, TEXT("ON START"));

		bShooting = true;
		ShootAC = PlayWeaponSound(FireLoopSound);
		muzzlePSC = muzzleFlash(MuzzleFX);
		//WeaponTrace();
		GetWorldTimerManager().SetTimer(shootingTimer, this, &AWeapon::WeaponTrace, weaponFireRate, true);
	
}