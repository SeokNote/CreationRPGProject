// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Engine.h"
#include "Containers/Array.h"
#include "Engine/DamageEvents.h" 
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
//#include "MyWeapon.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyHealth = 100.f;
	MyMaxHealth = 500.f;

	Gold = 1000;

	SetupStimulusSource();

	//MyHealth = MyMaxHealth;
}

//******************
//***********Weapon******************
////USkeletalMeshComponent* ABasicCharacter::GetSpecificPawnMesh() const
////{
////	return GetMesh();
////}
////
////FName ABasicCharacter::GetWeaponAttachPoint() const
////{
////	return WeaponAttachPoint;
////}
////
////void ABasicCharacter::EquipWeapon(AMyWeapon* Weapon)
////{
////	if (Weapon)
////	{
////		SetCurrentWeapon(Weapon, CurrentWeapon);
////	}
////}

void ABasicCharacter::EquipWeapon(AWeapon* NewWeapon)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->OnUnequip();
		CurrentWeapon->Destroy();
	}

	CurrentWeapon = NewWeapon;
	CurrentWeapon->OnEquip();
}

AWeapon* ABasicCharacter::GetEquippedWeapon() const
{
	return CurrentWeapon;
}

void ABasicCharacter::RestoreHP(float hp)
{
	MyHealth += hp;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), MyHealth));
}

//void ABasicCharacter::AddWeapon(AMyWeapon* Weapon)
//{
//	if (Weapon)
//	{
//		Inventory.AddUnique(Weapon);
//	}
//}
//
//void ABasicCharacter::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon)
//{
//	AMyWeapon* LocalLastWeapon = NULL;
//	if (LastWeapon != NULL)
//	{
//		LocalLastWeapon = LastWeapon;
//	}
//
//	if (NewWeapon)
//	{
//		NewWeapon->SetOwningPawn(this);
//		NewWeapon->OnEquip(LastWeapon);
//	}
//}
//void ABasicCharacter::SpawndefaultInventory()
//{
//	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
//
//	if (DefaultInventoryClasses.Num() > 0)
//	{
//		FActorSpawnParameters SpawnInfo;
//		UWorld* WRLD = GetWorld();
//		AMyWeapon* NewWeapon = WRLD->SpawnActor<AMyWeapon>(DefaultInventoryClasses[0], SpawnInfo);
//		AddWeapon(NewWeapon);
//	}
//
//	if (Inventory.Num() > 0)
//	{
//		EquipWeapon(Inventory[0]);
//	}
//}
//****************************

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void ABasicCharacter::Attack()
//{
//}
////
////float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
////{
////	const float MyGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
////
////	if (MyHealth <= 0)
////	{
////		this->Destroy();
////	}
////	else
////	{
////		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), MyHealth));
////		MyHealth -= MyGetDamage;
////	}
////	PlayAnimMontage(BeHit_AnimMontage, 1.0f);
////
////	return MyGetDamage;
////}


float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float MyGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealth <= 0.0f)
	{
		return 0.0f;
	}

	if (MyHealth > 0.f)
	{
		MyHealth -= MyGetDamage;
	}

	if (MyHealth <= 0)
	{
		PlayAnimMontage(Death_AnimMontage, 1.0f);
		Die(MyGetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(MyGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), MyHealth));
	}


	return MyGetDamage;
}

void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage);
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	MyHealth = FMath::Min(0.f, MyHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasicCharacter::DeathAnimationEnd, DeathAnimDuration, false);
}

void ABasicCharacter::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

void ABasicCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

//void ABasicCharacter::WeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SwwepResult)
//{
//}



