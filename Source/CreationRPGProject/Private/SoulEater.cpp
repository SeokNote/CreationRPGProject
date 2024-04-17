// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulEater.h"

// Sets default values
ASoulEater::ASoulEater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoulEater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoulEater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoulEater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ASoulEater::GetBehaviorTree() const
{
	return Tree;
}

APatrolPath* ASoulEater::GetPatrolPath() const
{
	return PatrolPath;
}

UAnimMontage* ASoulEater::GetAttackMontage() const
{
	return AttackMontage;
}

int ASoulEater::MeleeAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}

	return 0;
}

