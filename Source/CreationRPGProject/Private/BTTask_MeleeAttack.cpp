// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"
#include "CreationRPGProject/Public/CombatInterface.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    auto const* const cont = OwnerComp.GetAIOwner();
    auto* const souleater = Cast<ASoulEater>(cont->GetPawn());

    if (auto* const icombat = Cast<ICombatInterface>(souleater))
    {
        if (AttackMontageHasFinished(souleater))
        {
            icombat->Execute_MeleeAttack(souleater);
        }
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::AttackMontageHasFinished(ASoulEater* const souleater)
{
    return souleater->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(souleater->GetAttackMontage());
}
