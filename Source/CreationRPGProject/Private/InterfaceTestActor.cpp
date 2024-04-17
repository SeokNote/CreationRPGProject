// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceTestActor.h"
#include "CreationRPGProject/Public/Shop/ShopInventoryPanel.h"
#include "CreationRPGProject/Public/Shop/ShopInventorySlot.h"

// Sets default values
AInterfaceTestActor::AInterfaceTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	SetRootComponent(Mesh);

	//static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataTable(TEXT("DataTable'/Game/ItemData.ShopDataTable'"));
	//ItemDataTableObject = ItemDataTable.Object;

}

// Called when the game starts or when spawned
void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteratableData = InstanceInteractableData;
}

void AInterfaceTestActor::LoadItemData()
{
	//if (!ItemDataTableObject) return;

	if (!ItemDataTable) return;

	// Array to hold the struct data
	TArray<FItemData*> OutItemData;
	ItemDataTable->GetAllRows<FItemData>(TEXT(""), OutItemData);

	for (const FItemData* ItemData : OutItemData)
	{
		// Here you can create item instances based on the loaded data
		// For example, log the item name
		UE_LOG(LogTemp, Warning, TEXT("Loaded Item: %s"), *ItemData->TextData.Name.ToString());
	}
}

UItemBase* AInterfaceTestActor::CreateItemInstance(const FItemData& ItemData)
{
	UItemBase* NewItem = NewObject<UItemBase>(this, UItemBase::StaticClass());
	if (!NewItem) return nullptr;

	// Set item properties from the data
	NewItem->ID = ItemData.ID;
	NewItem->ItemType = ItemData.ItemType;
	NewItem->ItemQuality = ItemData.ItemQuality;
	NewItem->ItemStatistics = ItemData.ItemStatistics;
	NewItem->TextData = ItemData.TextData;
	NewItem->NumericData = ItemData.NumericData;
	NewItem->AssetData = ItemData.AssetData;
	NewItem->Quantity = 1; // Default quantity

	return NewItem;
}

void AInterfaceTestActor::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on interface test actor."));
}

void AInterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on interface test actor."));
}

void AInterfaceTestActor::Interact(AKwang* PlayerCharacter)
{
	if (ItemDataTable)
	{
		TArray<FItemData*> OutItemData;
		ItemDataTable->GetAllRows<FItemData>(TEXT(""), OutItemData);

		for (const FItemData* ItemData : OutItemData)
		{
			UItemBase* ShopItem = CreateItemInstance(*ItemData);
			InventoryContents.Add(ShopItem);
		}
	}

	PlayerCharacter->ShopOpen();
	ShopInventoryPanel = PlayerCharacter->GetShopInventoryPanel();
	ShopInventoryPanel->RefreshInventory(InventoryContents);
	InventoryContents.Empty();

}

