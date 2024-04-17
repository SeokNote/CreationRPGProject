// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/ShopInventorySlot.h"
#include "CreationRPGProject/Public/ItemBase.h"
#include "CreationRPGProject/Kwang.h"
#include "CreationRPGProject/Public/Shop/ShopInventoryTooltip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UShopInventorySlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ToolTipClass)
    {
        UShopInventoryTooltip* ToolTip = CreateWidget<UShopInventoryTooltip>(this, ToolTipClass);
        ToolTip->InventorySlotBeingHovered = this;
        SetToolTip(ToolTip);
    }
}

void UShopInventorySlot::NativeConstruct()
{
    Super::NativeConstruct();
    if (ItemReference)
    {
        // ������ ǰ��, ������, �̸�, ���� ���� �����մϴ�.
        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
        //ItemName->SetText(FText::FromString(ItemReference->TextData.Name.ToString()));
        //ItemPrice->SetText(FText::AsNumber(ItemReference->ItemStatistics.SellValue));

        // ���⿡�� ǰ���� ���� ���� ���� �� �߰����� UI ������Ʈ�� ������ �� �ֽ��ϴ�.
    }
}

FReply UShopInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeomerty, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeomerty, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        AKwang* PlayerCharacter = Cast<AKwang>(GetOwningPlayerPawn());

        if (PlayerCharacter && PlayerCharacter->GetGold() >= ItemReference->ItemStatistics.SellValue)
            ItemReference->Shop(ItemReference, PlayerCharacter);
    }
    else
    {
        return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    // submenu on right click will happen here
    return Reply.Unhandled();
}
