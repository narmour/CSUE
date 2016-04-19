// Fill out your copyright notice in the Description page of Project Settings.

#include "CSUE.h"
#include "CSUEAICharacter.h"


// Sets default values
ACSUEAICharacter::ACSUEAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	myHealth = 100.f;


}

// Called when the game starts or when spawned
void ACSUEAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSUEAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACSUEAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ACSUEAICharacter::takeDamage(float damage) {
	myHealth -= damage;
	UE_LOG(LogTemp, Warning, TEXT("TOOK A HIT,   %f"), myHealth);
	//if we go negative reset back to 0
	if (myHealth < 0)
		myHealth = 0;
}

