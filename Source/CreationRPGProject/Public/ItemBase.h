// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreationRPGProject/Public/Structs.h"
#include "CreationRPGProject/Kwang.h"
#include "ItemBase.generated.h"

/**
 * 
 */

class UInventoryComponent;

UCLASS()
class CREATIONRPGPROJECT_API UItemBase : public UObject
{
	GENERATED_BODY()
	

public:
	//---------------------------------------------------------------
	//PROPERTIES & VARIABLES
	//---------------------------------------------------------------
	UPROPERTY()
	UInventoryComponent* OwningInventory;

	AActor* OwningActor;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	int32 Quantity;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;

	bool bIsCopy;
	bool bIsPickup;

	//---------------------------------------------------------------
    //FUNCTIONS
    //---------------------------------------------------------------
	UItemBase();

	void ResetItemFlags();

	UItemBase* CreateItemCopy() const;
	UItemBase* CurrentItemBase;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(UItemBase* ItemIn, AKwang* Character);

	UFUNCTION(Category = "ShopItem")
	virtual void Shop(UItemBase* ItemIn, AKwang* Character);

protected:
	bool operator == (const FName& OtherID) const
	{
		return this->ID == OtherID;
	}


public:


};
