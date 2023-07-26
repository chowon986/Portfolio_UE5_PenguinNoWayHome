// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/ProgressBar.h>
#include <Components/Image.h>
#include "Blueprint/UserWidget.h"
#include "HPBarBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API UHPBarBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

private:
	UImage* imageHPBase;
	UProgressBar* progressbarHP;

};
