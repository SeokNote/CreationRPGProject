// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TitleCameraPawn.generated.h"

UCLASS()
class CREATIONRPGPROJECT_API ATitleCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATitleCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere)
	FVector StartLocation = FVector::Zero();
	UPROPERTY(EditAnywhere)
	FVector EndLocation = { 5000.f,0.f,0.f };
	UPROPERTY(EditAnywhere)
	float Velocity = 1000.f;
};
