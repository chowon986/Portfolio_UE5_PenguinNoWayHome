// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "MVVMViewModelBase.h"
#include "PlayerStateViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API UPlayerStateViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UPlayerStateViewModel();

	UFUNCTION(BlueprintCallable)
		void SetCurrentHealth(float NewCurrentHealth);
	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth() const { return currentHealth; }
	UFUNCTION(BlueprintPure, FieldNotify)
		float GetHealthPercent() const { return currentHealth / maxHealth; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentFly(float NewCurrentFly);
	UFUNCTION(BlueprintCallable)
		float GetCurrentFly() const { return currentFly; }
	UFUNCTION(BlueprintPure, FieldNotify)
		float GetFlyPercent() const { return currentFly / maxFly; }

private:
	void OnPlayerHPChanged(float HP);
	void OnPlayerFlyChanged(float Fly);

public:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetCurrentHealth", Getter = "GetCurrentHealth")
	float currentHealth;

	UPROPERTY()
	float maxHealth;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetCurrentFly", Getter = "GetCurrentFly")
	float currentFly;

	UPROPERTY()
	float maxFly;
};
