// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "InteractableInterface.h"

void UInteractionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    KeyPressText->SetText(FText::FromString("Press"));
    CurrentInteractionDuration = 0.0f;
}

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
    switch (InteractableData->InteractableType)
    {
    case EInteratableType::PickUp:
        KeyPressText->SetText(FText::FromString("Press"));
        InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

        if (InteractableData->Quantity < 2)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
        else
        {
            QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"),
                InteractableData->Quantity));
            QuantityText->SetVisibility(ESlateVisibility::Visible);
        }
        break;

    case EInteratableType::NonPlayerCharacter:
        break;

    case EInteratableType::Device:
        break;

    case EInteratableType::Toggle:
        break;

    case EInteratableType::Container:
        break;

    default: ;
    }

    ActionText->SetText(InteractableData->Action);
    NameText->SetText(InteractableData->Name);
}

float UInteractionWidget::UpdateInteractionProgress()
{
    return 0.0f;
}

