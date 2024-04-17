// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/ShopInventoryPanel.h"
#include "CreationRPGProject/Kwang.h"
#include "CreationRPGProject/Public/Shop/ShopInventorySlot.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"


void UShopInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    PlayerCharacter = Cast<AKwang>(GetOwningPlayerPawn());

    PlayerCharacter->SetShopInventoryPanel(this);

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UShopInventoryPanel::OnCloseButtonClicked);
    }
}

void UShopInventoryPanel::RefreshInventory(const TArray<UItemBase*>& InventoryContents)
{
    // 기존에 패널에 추가된 모든 아이템 슬롯을 제거합니다.
    InventoryPanel->ClearChildren();

    // InventoryContents 배열을 순회합니다.
    for (UItemBase* InventoryItem : InventoryContents)
    {
        // 각 아이템에 대한 UShopInventorySlot 위젯 인스턴스를 생성합니다.
        UShopInventorySlot* ItemSlot = CreateWidget<UShopInventorySlot>(this, ShopInventorySlotClass);
        if (ItemSlot)
        {
            // 아이템 참조를 슬롯에 설정합니다.
            ItemSlot->SetItemReference(InventoryItem);

            // 슬롯을 인벤토리 패널에 추가합니다.
            InventoryPanel->AddChildToWrapBox(ItemSlot);
        }
    }
}

void UShopInventoryPanel::OnCloseButtonClicked()
{
    PlayerCharacter->ShopClose();
}
