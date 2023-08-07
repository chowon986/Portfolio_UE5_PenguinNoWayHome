// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components\Image.h>
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

	UFUNCTION()
	void OnHoverButton();

	UFUNCTION()
	void UnOnHoverButton();

	void SetMainHUD(UUserWidget* MainHUD);
	void PlayWidgetAnimation(FString AnimationName);

private:
	UButton* startButton;
	UMainHUDBase* mainHUD;
	UTextBlock* startText;
	TMap<FString, UWidgetAnimation*> widgetAnimations;
};
