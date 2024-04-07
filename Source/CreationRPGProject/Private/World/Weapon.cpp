// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Weapon.h"
#include "CreationRPGProject/Kwang.h"

// Sets default values

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

AWeapon::AWeapon()
{
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::InitializeForCharacter(AKwang* InPlayerCharacter)
{
	PlayerCharacter = InPlayerCharacter;
}


USkeletalMeshComponent* AWeapon::GetWeaponMesh() const
{
	return WeaponMesh;
}

void AWeapon::OnEquip()
{
	if (!PlayerCharacter) return;

	const FName SocketName(TEXT("DamageSocket")); // 적절한 소켓 이름으로 변경해주세요
	AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AWeapon::OnUnequip()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}



