// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopMainMenu.generated.h"

/**
 * 
 */
class AKwang;
UCLASS()
class CREATIONRPGPROJECT_API UShopMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	AKwang* PlayerCharacter;

protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativeConstruct() override;

};
