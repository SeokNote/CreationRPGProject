// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"
#include "CreationRPGProject/Public/SoulEater.h"
#include "CreationRPGProject/Public/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			auto const Index = bc->GetValueAsInt(GetSelectedBlackboardKey());

			if (auto* souleater = Cast<ASoulEater>(cont->GetPawn()))
			{
				auto const Point = souleater->GetPatrolPath()->GetPatrolPoint(Index);

				auto const GlobalPoint = souleater->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
