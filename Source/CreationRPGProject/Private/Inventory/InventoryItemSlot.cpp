// Fill out your copyright notice in the Description page of Project Settings.


#include "CreationRPGProject/Public/Inventory/InventoryItemSlot.h"
#include "CreationRPGProject/Public/Inventory/DragItemVisual.h"
#include "CreationRPGProject/Public/Inventory/ItemDragDropOperation.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CreationRPGProject/Public/Inventory/InventoryTooltip.h"
#include "CreationRPGProject/Public/World/Weapon.h"
#include "CreationRPGProject/Public/ItemBase.h"

void UInventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ToolTipClass)
    {
        UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
        ToolTip->InventorySlotBeingHovered = this;
        SetToolTip(ToolTip);
    }
}

void UInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();
    if (ItemReference)
    {
        switch (ItemReference->ItemQuality)
        {
        case EItemQuality::Shoddy:
            ItemBorder->SetBrushColor(FLinearColor::Gray);
            break;
        case EItemQuality::Common:
            ItemBorder->SetBrushColor(FLinearColor::White);
            break;
        case EItemQuality::Quality:
            ItemBorder->SetBrushColor(FLinearColor::Green);
            break;
        case EItemQuality::Masterwork:
            ItemBorder->SetBrushColor(FLinearColor::Blue);
            break;
        case EItemQuality::Grandmaster:
            ItemBorder->SetBrushColor(FLinearColor(100.0f,65.0f,0.0f,1.0f)); // Orange
            break;
        default: ;
        }

        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

        if (ItemReference->NumericData.bIsStackable)
        {
            ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
        }
        else
        {
            ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeomerty, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeomerty, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (ItemReference->ItemType == EItemType::Weapon)
        {
            AKwang* PlayerCharacter = Cast<AKwang>(GetOwningPlayerPawn());

            if (PlayerCharacter)
            {
                // 저장된 무기를 가져오고 새로운 무기로 교체합니다.
                AWeapon* EquippedWeapon = PlayerCharacter->GetEquippedWeapon();
                if (EquippedWeapon)
                {
                    // 예전 무기를 제거하고 새로운 무기를 장착합니다.
                    EquippedWeapon->Destroy();
                }

                // 새로운 무기 생성 및 플레이어에 장착
                USkeletalMesh* ItemStaticMesh = ItemReference->AssetData.SkeletalMesh;
                AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());

                if (NewWeapon && PlayerCharacter)
                {
                    // 무기에 SkeletalMesh 설정
                    NewWeapon->GetWeaponMesh()->SetSkeletalMesh(ItemStaticMesh);

                    // 무기를 PlayerCharacter에게 초기화
                    NewWeapon->InitializeForCharacter(PlayerCharacter);

                    // PlayerCharacter에 무기 장착 처리
                    PlayerCharacter->EquipWeapon(NewWeapon);

                    ItemReference->Use(ItemReference, PlayerCharacter);

                    PlayerCharacter->SetCurrentWeaponItemBase(ItemReference);
                }
            }
        }
        if(ItemReference->ID == FName(TEXT("test_001")))
        {
             AKwang* PlayerCharacter = Cast<AKwang>(GetOwningPlayerPawn());
             ItemReference->Use(ItemReference,PlayerCharacter);
             ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
        }
    }
    else
    {
        return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    // submenu on right click will happen here
    return Reply.Unhandled();
}


void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeomerty, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeomerty, InMouseEvent, OutOperation);

    if (DragItemVisualClass)
    {
        const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
        DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
        DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
        DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

        ItemReference->NumericData.bIsStackable
            ? DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity))
            : DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

        UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
        DragItemOperation->SourceItem = ItemReference;
        DragItemOperation->SourceInventory = ItemReference->OwningInventory;

        DragItemOperation->DefaultDragVisual = DragVisual;
        DragItemOperation->Pivot = EDragPivot::TopLeft;

        OutOperation = DragItemOperation;
    }
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDrageDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDrageDropEvent, InOperation);
}
