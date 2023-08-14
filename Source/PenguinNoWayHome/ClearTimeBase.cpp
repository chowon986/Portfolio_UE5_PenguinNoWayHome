// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearTimeBase.h"
#include "PlayerCharacterController.h"
#include "PlayerCharacterBase.h"
#include "PenguinNoWayHomeGameModeBase.h"

void UClearTimeBase::NativeConstruct()
{
	Super::NativeConstruct();
	countTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("ClearTime")));
}

void UClearTimeBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void UClearTimeBase::SetCountTimeText()
{
	UWorld* curWorld = GetWorld();
	
	if (IsValid(curWorld))
	{
		APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(curWorld));

		if (IsValid(controller))
		{
			float curTime = controller->GetClearTime();
			int32 Hours = FMath::FloorToInt(curTime / 3600);
			int32 Minutes = FMath::FloorToInt((curTime - (Hours * 3600)) / 60);
			int32 Seconds = FMath::RoundToInt(curTime - (Hours * 3600) - (Minutes * 60));

			FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Minutes, Seconds);

			APenguinNoWayHomeGameModeBase* gameMode = Cast<APenguinNoWayHomeGameModeBase>(curWorld->GetAuthGameMode());

			if (IsValid(gameMode))
				gameMode->Save(Hours, Minutes, Seconds);

			countTime->SetText(FText::FromString(TimeString));
		}
	}
}