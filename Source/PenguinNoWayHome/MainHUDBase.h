// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "MainHUDBase.generated.h"

/**
 * 
 */
class USettingBase;
class UTitleBase;
class UClearTimeBase;
UCLASS()
class PENGUINNOWAYHOME_API UMainHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	void OnClearTimeChanged(bool value);

	UFUNCTION()
	void ClickSettingButton();

public:
	UClearTimeBase* clearTime;

	bool onceCheck;
	bool isOnSettingButton;
	UTitleBase* title;
	UButton* SettingButton;
	USettingBase* Setting;
};
