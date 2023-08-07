// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDBase.generated.h"

/**
 * 
 */
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
	void ChangeLevel(FString nextLevel);

public:/*
	UHPBarBase* hpBar;*/
	UClearTimeBase* clearTime;
	bool onceCheck;
	UTitleBase* title;
};
