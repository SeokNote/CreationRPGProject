// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "Kwang.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage"/Game/Animations/))
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<AKwang>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();

			FRotator const AimRotation = Character->GetBaseAimRotation();
			FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());

			MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		}
	}
}

