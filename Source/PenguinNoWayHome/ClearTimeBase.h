// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <Components/TextBlock.h>
#include "Blueprint/UserWidget.h"
#include "ClearTimeBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API UClearTimeBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	void SetCountTimeText();

private:
	UTextBlock* countTime;
};
