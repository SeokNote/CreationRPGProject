// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BasicCharacter.h"
#include "Kwang.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CREATIONRPGPROJECT_API AKwang : public ABasicCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKwang();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	bool IsAttacking();

public:
	// Event handler for montage notify begin
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);
	


};
