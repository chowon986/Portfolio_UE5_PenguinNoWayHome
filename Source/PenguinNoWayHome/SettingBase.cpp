// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingBase.h"
#include "MainHUDBase.h"
#include "PlayerCharacterController.h"

void USettingBase::NativeConstruct()
{
	Super::NativeConstruct();

	isMusicOn = true;
	isSoundOn = true;

	backButton = Cast<UButton>(GetWidgetFromName("BackButton"));
	if (IsValid(backButton))
		backButton->OnClicked.AddDynamic(this, &USettingBase::ClickBackButton);

	titleButton = Cast<UButton>(GetWidgetFromName("TitleButton"));
	if (IsValid(titleButton))
		titleButton->OnClicked.AddDynamic(this, &USettingBase::ClickTitleButton);


	musicButton = Cast<UButton>(GetWidgetFromName("MusicButton"));
	if(IsValid(musicButton))
		musicButton->OnClicked.AddDynamic(this, &USettingBase::ClickMusicButton);

	soundButton = Cast<UButton>(GetWidgetFromName("SoundButton"));
	if(IsValid(soundButton))
		soundButton->OnClicked.AddDynamic(this, &USettingBase::ClickSoundButton);

	musicToggleOn = Cast<UImage>(GetWidgetFromName("MusicToggleOn"));
	musicToggleOff = Cast<UImage>(GetWidgetFromName("MusicToggleOff"));
	soundToggleOn = Cast<UImage>(GetWidgetFromName("SoundToggleOn"));
	soundToggleOff = Cast<UImage>(GetWidgetFromName("SoundToggleOff"));
}

void USettingBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void USettingBase::ClickBackButton()
{
	if (mainHUD)
		mainHUD->ClickSettingButton();
}

void USettingBase::ClickTitleButton()
{
	if (mainHUD)
	{
		mainHUD->ClickSettingButton();
		UGameplayStatics::OpenLevel(this, "TitleLevel");
	}
}

void USettingBase::ClickMusicButton()
{
	isMusicOn = !isMusicOn;

	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));
	if (IsValid(controller))
		controller->OnOffMusic(isMusicOn);

	if (isMusicOn)
	{
		musicToggleOn->SetVisibility(ESlateVisibility::Visible);
		musicToggleOff->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		musicToggleOn->SetVisibility(ESlateVisibility::Hidden);
		musicToggleOff->SetVisibility(ESlateVisibility::Visible);
	}
}

void USettingBase::ClickSoundButton()
{
	isSoundOn = !isSoundOn;

	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));
	if (IsValid(controller))
		controller->OnOffSound(isSoundOn);

	if (isSoundOn)
	{
		soundToggleOn->SetVisibility(ESlateVisibility::Visible);
		soundToggleOff->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		soundToggleOn->SetVisibility(ESlateVisibility::Hidden);
		soundToggleOff->SetVisibility(ESlateVisibility::Visible);
	}
}

void USettingBase::SetMainHUD(UMainHUDBase* MainHUD)
{
	mainHUD = MainHUD;
}
