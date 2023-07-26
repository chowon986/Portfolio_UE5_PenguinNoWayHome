// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDBase.h"
#include "HPBarBase.h"

void UMainHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	hpBar = Cast<UHPBarBase>(GetWidgetFromName(FName(TEXT("HPBar"))));
	if (IsValid(hpBar))
		hpBar->SetVisibility(ESlateVisibility::Visible);
}

void UMainHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}
