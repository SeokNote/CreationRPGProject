// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Item.generated.h"

UCLASS()
class CREATIONRPGPROJECT_API AItem : public AActor , public UInteractableInterface

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UStaticMeshComponent* ItemMesh;

	virtual void BeginPlay() override;

public:
	virtual void Interact() override;


};
