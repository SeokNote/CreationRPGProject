// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "CreationRPGProject/BasicCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CreationRPGProject/Public/SoulEater.h"

//#include "Perception/AIPerceptionComponent.h"
//#include "Perception/AISenseConfig_Sight.h"
//#include "CreationRPGProject/BasicCharacter.h"
//#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


//AMonsterAIController::AMonsterAIController()
//{
//	PrimaryActorTick.bCanEverTick = true;
//	SetUp_Perception();
//}
//
//void AMonsterAIController::BeginPlay()
//{
//	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("All System set !"));
//	if (GetPerceptionComponent() != nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("All System set !"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("No Componet !"));
//	}
//}
//
//void AMonsterAIController::OnPossess(APawn* _Pawn)
//{
//	Super::OnPossess(_Pawn);
//}
//
//void AMonsterAIController::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	APawn* ControlledPawn = GetPawn();
//	ABasicCharacter* Player = Cast<ABasicCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	if (ControlledPawn && Player && bIsPlayerDeteted)
//	{
//		MoveToActor(Player, 5.0f, true, true, true, 0, true);
//
//		FVector DirectionToPlayer = Player->GetActorLocation() - ControlledPawn->GetActorLocation();
//		DirectionToPlayer.Z = 0;
//		FRotator TargetRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
//
//		UE_LOG(LogTemp, Warning, TEXT("Target Rotation: %s"), *TargetRotation.ToString());
//		// 직접 Actor 회전을 설정
//		ControlledPawn->SetActorRotation(TargetRotation);
//	}
//}
//
//FRotator AMonsterAIController::GetControlRotation() const
//{
//	//if (GetPawn() == nullptr)
//	//{
//	//	return FRotator(0.0f, 0.0f, 0.0f);
//	//}
//
//	//ABasicCharacter* Player = Cast<ABasicCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
//	//if (Player && bIsPlayerDeteted)
//	//{
//	//	FVector DirectionToPlayer = Player->GetActorLocation() - GetPawn()->GetActorLocation();
//	//	DirectionToPlayer.Z = 0;  // Z축 영향 제거
//	//	return FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
//	//}
//
//	//// 다른 조건에 맞지 않을 때는 기본 ControlRotation을 반환
//	return Super::GetControlRotation();
//}
//
//void AMonsterAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
//{
//	if (DetectedPawns.Num() > 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("No Componet !"));
//	}
//	bIsPlayerDeteted = true;
//}
//
//void AMonsterAIController::SetUp_Perception()
//{
//	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
//	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
//
//	SightConfig->SightRadius = AISightRadius;
//	SightConfig->LoseSightRadius = AILoseSightRadius;
//	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
//	SightConfig->SetMaxAge(AISightAge);
//
//	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
//	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
//	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
//
//	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
//	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnPawnDetected);
//	GetPerceptionComponent()->ConfigureSense(*SightConfig);
//}

AMonsterAIController::AMonsterAIController(FObjectInitializer const& ObjectInitializer)
{
	SetUpPerceptionSystem();
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ASoulEater* const souleater = Cast<ASoulEater>(InPawn))
	{
		if (UBehaviorTree* const tree = souleater->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

void AMonsterAIController::SetUpPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

		if (SightConfig)
		{
			SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
			SightConfig->SightRadius = 500.f;
			SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
			SightConfig->PeripheralVisionAngleDegrees = 90.f;
			SightConfig->SetMaxAge(5.f);
			SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
			SightConfig->DetectionByAffiliation.bDetectEnemies = true;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

			GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
			GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetDetected);
			GetPerceptionComponent()->ConfigureSense(*SightConfig);
		}

}

void AMonsterAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const ch = Cast<ABasicCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
