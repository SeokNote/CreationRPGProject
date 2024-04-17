// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopInventorySlot.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UBorder;
class UShopInventoryTooltip;
//class UDragItemVisual;
class UItemBase;
UCLASS()
class CREATIONRPGPROJECT_API UShopInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; };
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; };

protected:
	//UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	//TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UShopInventoryTooltip> ToolTipClass;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* ItemName;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* ItemPrice;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeomerty, const FPointerEvent& InMouseEvent) override;
	//virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	//virtual void NativeOnDragDetected(const FGeometry& InGeomerty, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDrageDropEvent, UDragDropOperation* InOperation) override;
};