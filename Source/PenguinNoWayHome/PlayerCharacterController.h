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
	void PlayClickButton();
	void ChangeLevel();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	float clearTime;
	bool canCountTime;

	FTimerHandle timerHandle;

public:
	CountTimeEvent OnPlayerCountTimeEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAudioComponent* audioComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAudioComponent* effectAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* bgm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* clickButton;
};
