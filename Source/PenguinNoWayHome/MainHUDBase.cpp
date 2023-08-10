// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDBase.h"
#include "ClearTimeBase.h"
#include "TitleBase.h"
#include "SettingBase.h"
#include "PlayerCharacterController.h"

void UMainHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	clearTime = Cast<UClearTimeBase>(GetWidgetFromName(FName(TEXT("ClearTime"))));
	if (IsValid(clearTime))
		clearTime->SetVisibility(ESlateVisibility::Hidden);

	title = Cast<UTitleBase>(GetWidgetFromName(FName(TEXT("Title"))));

	if ("TitleLevel" == GetWorld()->GetName())
		title->SetVisibility(ESlateVisibility::Visible);
	else
		title->SetVisibility(ESlateVisibility::Hidden);

	if (IsValid(title))
		title->SetMainHUD(this);
	
	SettingButton = Cast<UButton>(GetWidgetFromName(FName(TEXT("SettingBtn"))));
	if (IsValid(SettingButton))
		SettingButton->OnClicked.AddDynamic(this, &UMainHUDBase::ClickSettingButton);

	Setting = Cast<USettingBase>(GetWidgetFromName(FName(TEXT("Setting"))));
	if (IsValid(Setting))
	{
		Setting->SetVisibility(ESlateVisibility::Hidden);
		Setting->SetMainHUD(this);
	}

	onceCheck = false;
	isOnSettingButton = false;
}

void UMainHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));
	if (IsValid(controller) && !onceCheck)
	{
		controller->OnPlayerCountTimeEvent.AddUObject(this, &UMainHUDBase::OnClearTimeChanged);
		onceCheck = true;
	}
}

void UMainHUDBase::OnClearTimeChanged(bool value)
{
	if (value == false)
	{
		clearTime->SetCountTimeText();
		clearTime->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainHUDBase::ClickSettingButton()
{
	isOnSettingButton = !isOnSettingButton;

	if (isOnSettingButton)
		Setting->SetVisibility(ESlateVisibility::Visible);
	else
		Setting->SetVisibility(ESlateVisibility::Hidden);
}
