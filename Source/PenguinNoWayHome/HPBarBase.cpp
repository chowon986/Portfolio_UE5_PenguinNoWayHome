// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarBase.h"

void UHPBarBase::NativeConstruct()
{
	Super::NativeConstruct();

	imageHPBase = Cast<UImage>(GetWidgetFromName(FName(TEXT("ImageBaseHP"))));
	if(IsValid(imageHPBase))
		imageHPBase->SetVisibility(ESlateVisibility::Visible);
	
	progressbarHP = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("ProgressBarHP"))));
	if(IsValid(progressbarHP))
		progressbarHP->SetVisibility(ESlateVisibility::Visible);
}

void UHPBarBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

}
