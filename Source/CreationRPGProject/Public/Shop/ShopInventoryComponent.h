// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnShopInventoryUpdated);
class UItemBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CREATIONRPGPROJECT_API UShopInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnShopInventoryUpdated OnShopInventoryUpdated;
	// Sets default values for this component's properties
	UShopInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	//UFUNCTION(Category = "Inventory")
	//UItemBase* FindMatchingItem(UItemBase* ItemIn) const;
	//UFUNCTION(Category = "Inventory")
	//UItemBase* FindNextItemByID(UItemBase* ItemIn) const;

	//UFUNCTION(Category = "Inventory")
	//void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove);
	//UFUNCTION(Category = "Inventory")
	//int32 RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove);

};
