// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BasicCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ADragonAIController::ADragonAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	SetUp_Perception();
}

void ADragonAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("All System set !"));
	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("All System set !"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Componet !"));

	}
}

void ADragonAIController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);
}

void ADragonAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABasicCharacter* Player01 = Cast<ABasicCharacter>(GetPawn());
	if (bIsPlayerDeteted == true)
	{
		ABasicCharacter* Player02 = Cast<ABasicCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MoveToActor(Player02, 5.0f);
	}
}

FRotator ADragonAIController::GetControlRotation() const
{

	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f,GetPawn()->GetActorRotation().Yaw,0.0f);
}

void ADragonAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	if (DetectedPawns.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Componet !"));
	}
	bIsPlayerDeteted = true;
}

void ADragonAIController::SetUp_Perception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ADragonAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
