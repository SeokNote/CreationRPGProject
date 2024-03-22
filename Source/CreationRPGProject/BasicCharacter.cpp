// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Engine.h"
#include "Containers/Array.h"
#include "MyWeapon.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Attacking = false;
	ComboAttack_Num = 0;

	MyHealth = 0.f;
	MyMaxHealth = 100.f;

	MyHealth = MyMaxHealth;
}

//******************
//***********Weapon******************
USkeletalMeshComponent* ABasicCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName ABasicCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABasicCharacter::EquipWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABasicCharacter::AddWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon)
{
	AMyWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}
void ABasicCharacter::SpawndefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	if (DefaultInventoryClasses.Num() > 0)
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AMyWeapon* NewWeapon = WRLD->SpawnActor<AMyWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		AddWeapon(NewWeapon);
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}
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

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float MyGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealth <= 0)
	{
		this->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), MyHealth));
		MyHealth -= MyGetDamage;
	}
	PlayAnimMontage(BeHit_AnimMontage, 1.0f);

	return MyGetDamage;
}

void ABasicCharacter::Attack()
{
	if (!Attacking)
	{
		if (ComboAttack_Num < 3)
		{
			int tmp_Num = rand() % 3 + 1;
			FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));
			ComboAttack_Num++;

			Attacking = true;

		}
		else
		{
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName("Attack_4"));
			ComboAttack_Num = 0;
		}
	}
}

void ABasicCharacter::Attack_End()
{
	Attacking = false;
}


void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{

}



