// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

//class UWidgetComponent;
UCLASS()
class CREATIONRPGPROJECT_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHealth() const;
	float GetMaxHealth() const;
	void SetHealth(float const NewHealth);

private:
	UPROPERTY()
	class UWidgetComponent* WidgetComponent;
	float const MaxHealth{ 100.f };
	float Health;


};
