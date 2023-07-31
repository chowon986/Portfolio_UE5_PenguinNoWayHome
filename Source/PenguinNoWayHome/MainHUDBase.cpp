// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDBase.h"
#include "ClearTimeBase.h"
#include "PlayerCharacterController.h"

void UMainHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	//hpBar = Cast<UHPBarBase>(GetWidgetFromName(FName(TEXT("HPBar"))));
	//if (IsValid(hpBar))
	//	hpBar->SetVisibility(ESlateVisibility::Visible);

	clearTime = Cast<UClearTimeBase>(GetWidgetFromName(FName(TEXT("ClearTime"))));
	if (IsValid(clearTime))
		clearTime->SetVisibility(ESlateVisibility::Hidden);

	onceCheck = false;
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
