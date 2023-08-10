// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "HPBarBase.h"
#include "GameFramework/GameModeBase.h"
#include "PenguinNoWayHomeGameModeBase.generated.h"

/**
 * 
 */
class UMainHUDBase;
UCLASS()
class PENGUINNOWAYHOME_API APenguinNoWayHomeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APenguinNoWayHomeGameModeBase();

public:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;

	UMainHUDBase* GetMainHUD() const { return mainHUD; }

public:
	UPROPERTY()
		UMainHUDBase* mainHUD;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> mainHUDClass;
};
