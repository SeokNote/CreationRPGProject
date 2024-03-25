// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFrameWork/Pawn.h"
#include "UObject/UObjectGlobals.h"
#include "BTTask_DragonRandom.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CREATIONRPGPROJECT_API UBTTask_DragonRandom : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTTask_DragonRandom(FObjectInitializer const& obj_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float search_radius = 1500.0f;

};
