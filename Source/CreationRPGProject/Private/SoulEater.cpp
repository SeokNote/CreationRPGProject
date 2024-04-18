// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulEater.h"
#include "CreationRPGProject/Kwang.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"

// Sets default values
ASoulEater::ASoulEater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MouthCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MouthCollider"));
	MouthCollider->SetupAttachment(GetMesh(), FName("MouthSocket")); // Assumes there is a socket named 'MouthSocket' at the mouth location
	MouthCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ASoulEater::BeginPlay()
{
	Super::BeginPlay();

	MouthCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoulEater::OnAttackOverlap);
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

void ASoulEater::EnableAttackCollider()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack collider enabled"));
	MouthCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	MouthCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MouthCollider->SetNotifyRigidBodyCollision(true);
}

void ASoulEater::DisableAttackCollider()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack collider disabled"));
	MouthCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	MouthCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MouthCollider->SetNotifyRigidBodyCollision(false);
}

void ASoulEater::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKwang* OverlappedKwang = Cast<AKwang>(OtherActor);

	if (OverlappedKwang)
	{
		auto const NewHealth = OverlappedKwang->GetHealth() - 10.f;
		OverlappedKwang->SetHealth(NewHealth);
		UE_LOG(LogTemp, Warning, TEXT("Kwang character hit by SoulEater! Health now: %f"), NewHealth);
	}
	// Damage logic here
}
