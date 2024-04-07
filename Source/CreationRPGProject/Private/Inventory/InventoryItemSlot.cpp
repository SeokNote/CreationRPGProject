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
                // ����� ���⸦ �������� ���ο� ����� ��ü�մϴ�.
                AWeapon* EquippedWeapon = PlayerCharacter->GetEquippedWeapon();
                if (EquippedWeapon)
                {
                    // ���� ���⸦ �����ϰ� ���ο� ���⸦ �����մϴ�.
                    EquippedWeapon->Destroy();
                }

                // ���ο� ���� ���� �� �÷��̾ ����
                USkeletalMesh* ItemStaticMesh = ItemReference->AssetData.SkeletalMesh;
                AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass());

                if (NewWeapon && PlayerCharacter)
                {
                    // ���⿡ SkeletalMesh ����
                    NewWeapon->GetWeaponMesh()->SetSkeletalMesh(ItemStaticMesh);

                    // ���⸦ PlayerCharacter���� �ʱ�ȭ
                    NewWeapon->InitializeForCharacter(PlayerCharacter);

                    // PlayerCharacter�� ���� ���� ó��
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
