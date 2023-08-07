// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleBase.h"
#include "MainHUDBase.h"

void UTitleBase::NativeConstruct()
{
	Super::NativeConstruct();

	startButton = Cast<UButton>(GetWidgetFromName(FName(TEXT("StartButton"))));
	if (startButton)
		startButton->OnClicked.AddDynamic(this, &UTitleBase::ClickStartButton);
}

void UTitleBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void UTitleBase::ClickStartButton()
{
	if (IsValid(mainHUD))
		mainHUD->ChangeLevel("StoryLevel");
}

void UTitleBase::SetMainHUD(UUserWidget* MainHUD)
{
	mainHUD = Cast<UMainHUDBase>(MainHUD);
}
