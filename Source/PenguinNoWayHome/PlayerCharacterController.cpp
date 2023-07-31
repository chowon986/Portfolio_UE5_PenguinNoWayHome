// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacterBase.h"

APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	clearTime = 0.f;
	canCountTime = true;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacterBase* player = Cast<APlayerCharacterBase>(GetCharacter());
	if (IsValid(player) && canCountTime == true)
	{
		if (player->GetIsCleared())
		{
			canCountTime = false;
			OnPlayerCountTimeEvent.Broadcast(canCountTime);
		}
		else if (player->GetState() == EPlayerState::Death)
		{
			// 재도전 UMG 띄우기
		}
	}

	if(canCountTime)
		clearTime += DeltaTime;
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void APlayerCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayerCharacterController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void APlayerCharacterController::OnUnPossess()
{
	Super::OnUnPossess();
}
