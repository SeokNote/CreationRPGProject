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

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	// 콜라이더의 상위 컴포넌트를 무기 메시로 설정
	WeaponCollider->SetupAttachment(WeaponMesh);
	// 콜라이더의 크기 설정
	WeaponCollider->InitBoxExtent(FVector(10.0f, 10.0f, 50.0f));
	WeaponCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));

	// 콜라이더의 충돌 설정
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WeaponCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

AWeapon::AWeapon()
{
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), WeaponCollider->GetComponentLocation(), FVector(10.f, 10.f, 50.f), FColor::Green, true, -1.0f, 0, 1);
}

void AWeapon::OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

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



