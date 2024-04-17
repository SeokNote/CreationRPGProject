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
        // 아이템 품질, 아이콘, 이름, 가격 등을 설정합니다.
        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
        //ItemName->SetText(FText::FromString(ItemReference->TextData.Name.ToString()));
        //ItemPrice->SetText(FText::AsNumber(ItemReference->ItemStatistics.SellValue));

        // 여기에서 품질에 따른 색상 변경 등 추가적인 UI 업데이트를 수행할 수 있습니다.
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
