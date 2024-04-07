// Fill out your copyright notice in the Description page of Project Settings.


//#include "MyWeapon.h"
//#include "Components/BoxComponent.h"
//#include "Engine.h"
//
//// Sets default values
//AMyWeapon::AMyWeapon(const FObjectInitializer& ObjectInitializer)
//	:Super(ObjectInitializer)
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
//	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	RootComponent = WeaponMesh;
//
//	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
//	WeaponCollision->SetBoxExtent(FVector(5.f, 5.f, 5.f));
//	WeaponCollision->SetupAttachment(WeaponMesh, "DamageSocket");
//
//	
//}
//
////void AMyWeapon::BeginPlay()
////{
////	Super::BeginPlay();
////
////	// Bind function to overlap event for weapon box
////	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::WeaponOverlap);
////	
////	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
////	WeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
////	WeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
////	WeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
////}
//
//void AMyWeapon::SetOwningPawn(ABasicCharacter* NewOwner)
//{
//	if (MyPawn != NewOwner)
//	{
//		MyPawn = NewOwner;
//	}
//}
//
//void AMyWeapon::AttachMeshToPawn()
//{
//	if (MyPawn)
//	{
//		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
//		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
//		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
//	}
//}
//
//void AMyWeapon::OnEquip(const AMyWeapon* LastWeapon)
//{
//	AttachMeshToPawn();
//}
//
////void AMyWeapon::WeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SwwepResult)
////{
////	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "ApplyDamage!");
////}
//
////void AMyWeapon::ActivateWeapon()
////{
////	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
////}
////
////void AMyWeapon::DeactivateWeapon()
////{
////	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
////}
//
//
//void AMyWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (OtherActor->IsA(AActor::StaticClass()) && OtherActor !=MyPawn && MyPawn->Attacking)
//	{
//		UGameplayStatics::ApplyDamage(OtherActor, 30.f, NULL, this, UDamageType::StaticClass());
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ApplyDamage!");
//	}
//}


