// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kwang.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyWeapon.generated.h"

UCLASS()
class CREATIONRPGPROJECT_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon(const FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(ABasicCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AMyWeapon* LastWeapon);

	//UFUNCTION()
	//void WeaponOverlap(
	//	UPrimitiveComponent* OverlappedComponent,
	//	AActor* OtherActor,
	//	UPrimitiveComponent* OtherComp,
	//	int32 OtherBodyIndex,
	//	bool bFromSweep,
	//	const FHitResult& SwwepResult);

	// Activate and deactivate weapon boxes
	//virtual void ActivateWeapon();
	//virtual void DeactivateWeapon();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UBoxComponent* WeaponCollision;
protected:
	class ABasicCharacter* MyPawn;

public:
	//virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

};
