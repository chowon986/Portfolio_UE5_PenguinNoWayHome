// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "TitleBase.generated.h"

/**
 * 
 */
class UMainHUDBase;
UCLASS()
class PENGUINNOWAYHOME_API UTitleBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	UFUNCTION()
	void ClickStartButton();

	void SetMainHUD(UUserWidget* MainHUD);

private:
	UButton* startButton;
	UMainHUDBase* mainHUD;
};
