// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "Math/Vector.h"
#include "CreationRPGProject/Public/HealthBarWidget.h"
//#include "CreationRPGProject/Public/Consts.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMonsterBase::AMonsterBase() 
	//: RightFirstCollisionBox{CreateDefaultSubobject<UBoxComponent>(TEXT("RightFirstCollisionBox"))}
	: WidgetComponent{ CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")) }
	, Health{MaxHealth}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(FVector(0.f,0.f,300.f));
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/UI/BP_HealthBar") };
		if (WidgetClass.Succeeded())
		{
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
		}
	}
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (auto const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		widget->SetBarValuePercent(Health / MaxHealth);
	}
}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonsterBase::GetHealth() const
{
	return Health;
}

float AMonsterBase::GetMaxHealth() const
{
	return MaxHealth;
}

void AMonsterBase::SetHealth(float const NewHealth)
{
	Health = NewHealth;
}

