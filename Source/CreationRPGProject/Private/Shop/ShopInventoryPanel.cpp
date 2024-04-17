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
    // ������ �гο� �߰��� ��� ������ ������ �����մϴ�.
    InventoryPanel->ClearChildren();

    // InventoryContents �迭�� ��ȸ�մϴ�.
    for (UItemBase* InventoryItem : InventoryContents)
    {
        // �� �����ۿ� ���� UShopInventorySlot ���� �ν��Ͻ��� �����մϴ�.
        UShopInventorySlot* ItemSlot = CreateWidget<UShopInventorySlot>(this, ShopInventorySlotClass);
        if (ItemSlot)
        {
            // ������ ������ ���Կ� �����մϴ�.
            ItemSlot->SetItemReference(InventoryItem);

            // ������ �κ��丮 �гο� �߰��մϴ�.
            InventoryPanel->AddChildToWrapBox(ItemSlot);
        }
    }
}

void UShopInventoryPanel::OnCloseButtonClicked()
{
    PlayerCharacter->ShopClose();
}
