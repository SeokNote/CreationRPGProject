// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SoulEaterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CREATIONRPGPROJECT_API USoulEaterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USoulEaterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;


	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, Meta = (AllowPrivateAccess = true))
	//float MovementOffsetYaw;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class APawn* SoulEaterPawn;
};
