// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreationRPGProject/public/InteractableInterface.h"
#include "Weapon.generated.h"

class UDataTable;
class UItemBase;


class AKwang;
UCLASS()
class CREATIONRPGPROJECT_API AWeapon : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    AWeapon(const FObjectInitializer& ObjectInitializer);

    AWeapon();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    void SetSkeletalMesh(USkeletalMeshComponent* Wm) { WeaponMesh = Wm; };

    USkeletalMeshComponent* GetWeaponMesh() const;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void OnEquip();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void OnUnequip();

    void InitializeForCharacter(AKwang* InPlayerCharacter);

private:
    AKwang* PlayerCharacter;

};