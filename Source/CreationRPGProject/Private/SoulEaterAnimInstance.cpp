// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulEaterAnimInstance.h"
#include "CreationRPGProject/Public/SoulEater.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

USoulEaterAnimInstance::USoulEaterAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void USoulEaterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto SoulEater = Cast<ASoulEater>(Pawn);
		if (SoulEater)
		{
			//FRotator const AimRotation = SoulEater->GetBaseAimRotation();
			//FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(SoulEater->GetVelocity());

			//MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		}
	}
}
