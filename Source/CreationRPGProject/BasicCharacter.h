// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreationRPGProject/Public/World/Weapon.h"
#include "BasicCharacter.generated.h"

class UItemBase;
UCLASS()
class CREATIONRPGPROJECT_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

	//USkeletalMeshComponent* GetSpecificPawnMesh() const;

	//FName GetWeaponAttachPoint()const;

	//void EquipWeapon(class AMyWeapon* Weapon);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AWeapon* CurrentWeapon;

	UItemBase* CurrentWeaponItemBase;

	void SetCurrentWeaponItemBase(UItemBase* CIB) { CurrentWeaponItemBase = CIB; };
	UItemBase* GetCurrentWeaponItemBase() { return CurrentWeaponItemBase; };


	UFUNCTION(BlueprintCallable, Category = "Player")
	void EquipWeapon(AWeapon* NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Player")
	AWeapon* GetEquippedWeapon() const;

	void RestoreHP(float hp);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= MyState)
	float MyHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float MyMaxHealth;

	int Gold;

	void AddGold(int gold) { Gold += gold; };
	void RemoveGold(int gold) { Gold -= gold; };
	int GetGold() { return Gold; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = Inventory)
	//FName WeaponAttachPoint;



	//TArray<class AMyWeapon*>Inventory;

	//class AMyWeapon* CurrentWeapon;

	//void AddWeapon(class AMyWeapon* Weapon);

	//void SetCurrentWeapon(class AMyWeapon* NewWeapon, class AMyWeapon* LastWeapon);

	//void SpawndefaultInventory();

	//UPROPERTY(EditDefaultsOnly, Category = Inventory)
	//TArray<TSubclassOf<class AMyWeapon>>DefaultInventoryClasses;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimMontage;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void DeathAnimationEnd();

	bool Attacking;


private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();

};
