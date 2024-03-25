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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	float AISightRadius = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	float AILoseSightRadius = AISightRadius + 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	float AIFieldOfView = 90.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	uint8 bIsPlayerDeteted : 1 = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DAI")
	float DistanceToPlayer = 0.0f;

private:
	UPROPERTY(EditInstanceOnly, Category = "DAI", meta = (AllowprivateAcces = "true"))
	class UBlackboardComponent* BlackboradComp;

	UPROPERTY(EditInstanceOnly, Category = "DAI", meta = (AllowprivateAcces = "true"))
	class UBehaviorTreeComponent* BehaviorComp;
	
	UPROPERTY(EditInstanceOnly, Category = "DAI", meta = (AllowprivateAcces = "true"))
	class UBehaviorTree* btree;

	UPROPERTY(EditInstanceOnly, Category = "DAI", meta = (AllowprivateAcces = "true"))
	class UAISenseConfig_Sight* SightConfig;

	void SetUp_Perception();
};
