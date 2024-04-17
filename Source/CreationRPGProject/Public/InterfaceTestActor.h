// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreationRPGProject/Kwang.h"
#include "InteractableInterface.h"
#include "CreationRPGProject/Public/ItemBase.h"
#include "CreationRPGProject/Public/Structs.h"
#include "InterfaceTestActor.generated.h"

class UDataTable;
class UShopInventoryPanel;
struct FItemData;
UCLASS()
class CREATIONRPGPROJECT_API AInterfaceTestActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceTestActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Test Actor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Test Actor")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditAnywhere, Category = "InventoryItems")
	TArray<FItemData> Items;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// ������ �����͸� �ε��ϴ� �Լ�
	void LoadItemData();

	// ������ �ν��Ͻ��� �����ϴ� �Լ�
	UItemBase* CreateItemInstance(const FItemData& ItemData);

	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AKwang* PlayerCharacter);

	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; };

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	UDataTable* ItemDataTable;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;

	UShopInventoryPanel* ShopInventoryPanel;

private:
	// ������ ���̺� ������Ʈ�� �����ϱ� ���� ������
	UDataTable* ItemDataTableObject;

};
