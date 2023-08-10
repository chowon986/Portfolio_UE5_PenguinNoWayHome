// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include "Blueprint/UserWidget.h"
#include "SettingBase.generated.h"

/**
 * 
 */
class UMainHUDBase;
UCLASS()
class PENGUINNOWAYHOME_API USettingBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;
	
	UFUNCTION()
	void ClickBackButton();

	UFUNCTION()
	void ClickTitleButton(); 
	
	UFUNCTION()
	void ClickMusicButton();

	UFUNCTION()
	void ClickSoundButton();

	void SetMainHUD(UMainHUDBase* MainHUD);

private:
	UButton* backButton;
	UButton* titleButton;
	UButton* musicButton;
	UButton* soundButton;
	UImage* musicToggleOn;
	UImage* musicToggleOff;
	UImage* soundToggleOn;
	UImage* soundToggleOff;

public:
	bool isMusicOn;
	bool isSoundOn;
	UMainHUDBase* mainHUD;
};
