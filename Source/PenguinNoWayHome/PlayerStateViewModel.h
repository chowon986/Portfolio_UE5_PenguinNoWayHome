// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	void OnPlayerHPChanged(float HP);

public:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetCurrentHealth", Getter = "GetCurrentHealth")
	float currentHealth;

	UPROPERTY()
	float maxHealth;
};
