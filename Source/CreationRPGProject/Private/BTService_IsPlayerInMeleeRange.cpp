// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"
#include "CreationRPGProject/Public/MonsterAIController.h"
#include "CreationRPGProject/Public/SoulEater.h"
#include "Runtime/Engine/Classes/Kismet/GamePlayStatics.h"
#include "GameFramework//Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto const* const souleater = Cast<ASoulEater>(cont->GetPawn());

	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), souleater->GetDistanceTo(player) <= MeleeRange);
}
