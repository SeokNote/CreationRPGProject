// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopInventoryPanel.generated.h"

/**
 * 
 */
class UWrapBox;
class UButton;
class UTextBlock;
class UShopInventoryComponent;
class UShopInventorySlot;
class AKwang;
UCLASS()
class CREATIONRPGPROJECT_API UShopInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UFUNCTION()
	void RefreshInventory(const TArray<UItemBase*>& InventoryContents);

	UPROPERTY(meta = (BindWidget))
	UWrapBox* InventoryPanel;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY()
	AKwang* PlayerCharacter;

	//UPROPERTY()
	//UInventoryComponent* InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShopInventorySlot> ShopInventorySlotClass;


protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnCloseButtonClicked(); // 버튼 클릭 이벤트 처리 함수 선언
};

