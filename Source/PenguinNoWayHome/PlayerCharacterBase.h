// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;
UCLASS()
class PENGUINNOWAYHOME_API APlayerCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	void Move(const FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* movementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* defaultContext;
};
