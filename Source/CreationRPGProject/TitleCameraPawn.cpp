// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleCameraPawn.h"

// Sets default values
ATitleCameraPawn::ATitleCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATitleCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATitleCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AddActorLocalRotation(GetActorRotation() * DeltaTime);
	//SetActorLocation(CurPos);
}

// Called to bind functionality to input
void ATitleCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

