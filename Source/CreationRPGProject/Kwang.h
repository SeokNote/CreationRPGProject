// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CreationRPGProject/BasicCharacter.h"
#include "CreationRPGProject/Public/InteractableInterface.h"
#include "Kwang.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};


	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;


};

class AMyHUD;
class UInventoryComponent;
class UItemBase;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UShopInventoryPanel;
class UInputAction;

UCLASS()
class CREATIONRPGPROJECT_API AKwang : public ABasicCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKwang();

	virtual void PostInitializeComponents() override;

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; };

	void UpdateInteractionWidget() const;

	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);

	void ShopOpen();
	void ShopClose();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AMyHUD* HUD;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractableInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	UInventoryComponent* PlayerInventory;

	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	void ToggleMenu();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnyWhere, Category = Input)
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnyWhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnyWhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnyWhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnyWhere, Category = Input)
	UInputAction* AttackAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontage;

	void Attack();

	int ComboAttackIndex = 0;

	void Running();
	void StopRunning();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunSpeed;

	UShopInventoryPanel* ShopInventoryPanel;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	bool IsAttacking();

	UShopInventoryPanel* GetShopInventoryPanel() { return ShopInventoryPanel; };
	void SetShopInventoryPanel(UShopInventoryPanel* SIP) { ShopInventoryPanel = SIP; };

public:
	// Event handler for montage notify begin
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);
	


};
