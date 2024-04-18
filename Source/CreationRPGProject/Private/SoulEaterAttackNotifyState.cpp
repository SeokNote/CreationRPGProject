// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulEaterAttackNotifyState.h"

#include "CreationRPGProject/Public/SoulEater.h"

void USoulEaterAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ASoulEater* const souleater = Cast<ASoulEater>(MeshComp->GetOwner()))
		{
			souleater->EnableAttackCollider();
		}
	}
}

void USoulEaterAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ASoulEater* const souleater = Cast<ASoulEater>(MeshComp->GetOwner()))
		{
			souleater->DisableAttackCollider();
		}
	}
}
