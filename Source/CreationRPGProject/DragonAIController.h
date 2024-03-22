// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DragonAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackbordComponent;
UCLASS(config=Game)
class CREATIONRPGPROJECT_API ADragonAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADragonAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* _Pawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

	float AISightRadius = 500.0f;
	float AISightAge = 5.0f;
	float AILoseSightRadius = AISightRadius + 50.f;
	float AIFieldOfView = 90.f;

	class UAISenseConfig_Sight* SightConfig;
private:
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboradComp;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;

};
