// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	DECLARE_EVENT_OneParam(APlayerCharacterController, CountTimeEvent, bool)

	
public:
	APlayerCharacterController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();
	virtual void PostInitializeComponents() override;

	float GetClearTime() { return clearTime; }


protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	float clearTime;
	bool canCountTime;

public:
	CountTimeEvent OnPlayerCountTimeEvent;
};
