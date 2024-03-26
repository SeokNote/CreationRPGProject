// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"
#include "Engine.h"
#include "BasicCharacter.h"
//#include "MyWeapon.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, __FUNCTION__);
			Player->Attacking = true;
		}
	}
	//if (MeshComp && MeshComp->GetOwner())
	//{
	//	AMyWeapon* Weapon = Cast<AMyWeapon>(MeshComp->GetOwner());
	//	if (Weapon != NULL)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, __FUNCTION__);
	//		Weapon->ActivateWeapon();
	//	}
	//}
}
void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, __FUNCTION__);
			Player->Attacking = false;
		}
	}
	////if (MeshComp && MeshComp->GetOwner())
	////{
	////	AMyWeapon* Weapon = Cast<AMyWeapon>(MeshComp->GetOwner());
	////	if (Weapon != NULL)
	////	{
	////		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, __FUNCTION__);
	////		Weapon->DeactivateWeapon();
	////	}
	////}
}
