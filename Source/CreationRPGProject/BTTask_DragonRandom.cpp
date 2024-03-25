// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DragonRandom.h"       
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "DragonAIController.h"
#include "Engine.h"
#include "Engine/World.h"

UBTTask_DragonRandom::UBTTask_DragonRandom(FObjectInitializer const& obj_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_DragonRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const cont = Cast<ADragonAIController>(OwnerComp.GetAIOwner());
	auto const monster = cont->GetPawn();

	FVector const origin = monster->GetActorLocation();
	FNavLocation loc;
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
	{
		//cont->GetBlackboardComponent()->SetValueAsVector(bbkeys::target_location, loc.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return  EBTNodeResult::Succeeded;
}
