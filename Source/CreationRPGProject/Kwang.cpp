// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyWeapon.h"


// Sets default values
AKwang::AKwang()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AKwang::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawndefaultInventory();
}


// Called when the game starts or when spawned
void AKwang::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}

	UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
	if (pAnimInst != nullptr)
	{
		pAnimInst->OnPlayMontageNotifyBegin.AddDynamic(this, &AKwang::HandleOnMontageNotifyBegin);
	}
}

void AKwang::Move(const FInputActionValue& Value)
{
		//if (ActionState != )
	if (!IsAttacking())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKwang::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);

}

// Called every frame4
void AKwang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKwang::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKwang::Attack);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AKwang::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKwang::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AKwang::Jump);
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AKwang::Attack);
	}

}

void AKwang::Attack()
{
	bool IsFall = GetMovementComponent()->IsFalling();

	if (!IsAttacking() && !IsFall)
	{
		UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
		if (pAnimInst != nullptr)
		{
			if (AttackMontage != nullptr)
			{
				pAnimInst->Montage_Play(AttackMontage);
			}
		}
	}
	else
	{
		ComboAttackIndex = 1;
	}

}

bool AKwang::IsAttacking()
{
	UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
	if (pAnimInst != nullptr)
	{
		if (pAnimInst->Montage_IsPlaying(AttackMontage))
		{
			return true;
		}
	}
	return false;
}


void AKwang::Jump()
{
	if(!IsAttacking())
	Super::Jump();
}

void AKwang::HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload)
{
	// Decrement Combo Index
	ComboAttackIndex--;

	if (ComboAttackIndex < 0)
	{
		//Get Anim Instance
		UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
		if (pAnimInst != nullptr)
		{
			pAnimInst->Montage_Stop(0.1f, AttackMontage);
		}
	}
}