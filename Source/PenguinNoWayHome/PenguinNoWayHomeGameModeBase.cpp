// Copyright Epic Games, Inc. All Rights Reserved.


#include "PenguinNoWayHomeGameModeBase.h"
#include "MainHUDBase.h"


APenguinNoWayHomeGameModeBase::APenguinNoWayHomeGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APenguinNoWayHomeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mainHUDClass))
	{
		mainHUD = Cast<UMainHUDBase>(CreateWidget(GetWorld(), mainHUDClass));
		if (mainHUD)
		{
			mainHUD->AddToViewport();
		}
	}
}

void APenguinNoWayHomeGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void APenguinNoWayHomeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void APenguinNoWayHomeGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
