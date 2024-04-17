// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
//class UProgressBar;
UCLASS()
class CREATIONRPGPROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value);
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HealthValue;

};
