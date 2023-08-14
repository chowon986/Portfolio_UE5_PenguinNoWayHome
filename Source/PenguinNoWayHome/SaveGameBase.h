// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API USaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:
	USaveGameBase();

public:
	UPROPERTY(VisibleAnywhere, Category = Time)
	FString saveSlotName;
	UPROPERTY(VisibleAnywhere, Category = Time)
	int32 saveIndex;
	UPROPERTY(VisibleAnywhere, Category = Time)
	int32 hours;
	UPROPERTY(VisibleAnywhere, Category = Time)
	int32 minutes;
	UPROPERTY(VisibleAnywhere, Category = Time)
	int32 seconds;
};
