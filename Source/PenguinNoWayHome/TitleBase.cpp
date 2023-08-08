// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleBase.h"
#include "MainHUDBase.h"
#include "PlayerCharacterController.h"
#include "Animation/WidgetAnimation.h"

void UTitleBase::NativeConstruct()
{
	Super::NativeConstruct();

	startButton = Cast<UButton>(GetWidgetFromName(FName(TEXT("StartButton"))));
	startText = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("StartText"))));
	if (IsValid(startButton))
	{
		startButton->OnClicked.AddDynamic(this, &UTitleBase::ClickStartButton);
		startButton->OnHovered.AddDynamic(this, &UTitleBase::OnHoverButton);
		startButton->OnUnhovered.AddDynamic(this, &UTitleBase::UnOnHoverButton);
	}

	UWidgetBlueprintGeneratedClass* widgetClass = GetWidgetTreeOwningClass();
	int size = widgetClass->Animations.Num();

	for (int i = 0; i < size; ++i)
	{
		FString name = widgetClass->Animations[i]->GetName();
		widgetAnimations.Add(name, widgetClass->Animations[i]);
	}
}

void UTitleBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void UTitleBase::ClickStartButton()
{
	UWorld* curWorld = GetWorld();
	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(curWorld));
	controller->PlayClickButton();
}

void UTitleBase::OnHoverButton()
{
	if (startText)
	{
		this->PlayWidgetAnimation("HoverAnimation_INST");
	}
}

void UTitleBase::UnOnHoverButton()
{
	if (startText)
	{
		this->PlayWidgetAnimation("UnHoverAnimation_INST");
	}
}

void UTitleBase::SetMainHUD(UUserWidget* MainHUD)
{
	mainHUD = Cast<UMainHUDBase>(MainHUD);
}

void UTitleBase::PlayWidgetAnimation(FString AnimationName)
{
	UWidgetAnimation* pAnim = widgetAnimations.FindRef(AnimationName);
	if (IsValid(pAnim))
	{
		PlayAnimation(pAnim);
	}
}
