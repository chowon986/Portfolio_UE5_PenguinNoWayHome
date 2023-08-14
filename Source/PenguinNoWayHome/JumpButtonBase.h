// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "JumpButtonBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API UJumpButtonBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

public:

	UFUNCTION()
	void ClickJumpButton();

private:
	UButton* jumpButton;
};
