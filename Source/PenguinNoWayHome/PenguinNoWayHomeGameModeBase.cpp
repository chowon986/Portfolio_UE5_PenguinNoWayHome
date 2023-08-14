// Copyright Epic Games, Inc. All Rights Reserved.


#include "PenguinNoWayHomeGameModeBase.h"
#include "MainHUDBase.h"
#include "SaveGameBase.h"


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

	Load();
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

void APenguinNoWayHomeGameModeBase::Save(int32 Hours, int32 Minutes, int32 Seconds)
{
	USaveGameBase* saveGameInstance = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));
	
	if (saveGameInstance)
	{
		saveGameInstance->saveSlotName = "SaveGame";
		saveGameInstance->saveIndex = 0;

		if (Hours < saveGameInstance->hours)
		{
			saveGameInstance->hours = Hours;
			saveGameInstance->minutes = Minutes;
			saveGameInstance->seconds = Seconds;
		}
		else if (Hours == saveGameInstance->hours)
		{
			if (Minutes < saveGameInstance->minutes)
			{
				saveGameInstance->hours = Hours;
				saveGameInstance->minutes = Minutes;
				saveGameInstance->seconds = Seconds;
			}
			else if (Minutes == saveGameInstance->minutes)
			{
				if (Seconds < saveGameInstance->seconds)
				{
					saveGameInstance->hours = Hours;
					saveGameInstance->minutes = Minutes;
					saveGameInstance->seconds = Seconds;
				}
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(saveGameInstance, saveGameInstance->saveSlotName, saveGameInstance->saveIndex);
	UE_LOG(LogTemp, Warning, TEXT("SaveTime : %d, %d, %d"), saveGameInstance->hours, saveGameInstance->minutes, saveGameInstance->seconds);

}

void APenguinNoWayHomeGameModeBase::Save()
{
	USaveGameBase* saveGameInstance = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));
	UGameplayStatics::SaveGameToSlot(saveGameInstance, saveGameInstance->saveSlotName, saveGameInstance->saveIndex);

	UE_LOG(LogTemp, Warning, TEXT("SaveTime : %d, %d, %d"), saveGameInstance->hours, saveGameInstance->minutes, saveGameInstance->seconds);
}

void APenguinNoWayHomeGameModeBase::Load()
{
	USaveGameBase* loadGameInstance = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));

	if (loadGameInstance)
	{
		loadGameInstance->saveSlotName = "SaveGame";
		loadGameInstance->saveIndex = 0;

		loadGameInstance = Cast<USaveGameBase>(UGameplayStatics::LoadGameFromSlot(loadGameInstance->saveSlotName, loadGameInstance->saveIndex));

		UE_LOG(LogTemp, Warning, TEXT("SaveTime : %d, %d, %d"), loadGameInstance->hours, loadGameInstance->minutes, loadGameInstance->seconds);
	}
}
