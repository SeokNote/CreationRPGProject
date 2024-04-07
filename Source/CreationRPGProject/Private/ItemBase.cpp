// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "CreationRPGProject/Kwang.h"
#include "CreationRPGProject/Public/World/Weapon.h"
#include "CreationRPGProject/Public/Components/InventoryComponent.h"

UItemBase::UItemBase()
	: bIsCopy(false)
	, bIsPickup(false)
{
}

void UItemBase::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->AssetData = this->AssetData;
	ItemCopy->bIsCopy = true;


	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);

		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
	}
}



void UItemBase::Use(UItemBase* ItemIn,AKwang* Character)
{
	if (ItemIn->ID == FName(TEXT("test_001"))) // 포션(ID = 임시)
	{
		Character->RestoreHP(50);
		OwningInventory->RemoveAmountOfItem(ItemIn, 1);

		//ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
	}

	if (ItemIn->ItemType == EItemType::Weapon)
	{
		if (Character)
			CurrentItemBase = Character->GetCurrentWeaponItemBase();

		if (CurrentItemBase)
		{
			OwningInventory->RemoveAmountOfItem(ItemIn, 1);
			OwningInventory->RemoveSingleInstanceOfItem(this);
			const FItemAddResult AddResult = OwningInventory->HandleAddItem(CurrentItemBase);
		}
		if (!CurrentItemBase)
		{
			OwningInventory->RemoveAmountOfItem(ItemIn, 1);
			OwningInventory->RemoveSingleInstanceOfItem(this);
		}
	}
}
