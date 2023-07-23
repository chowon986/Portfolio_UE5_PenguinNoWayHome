// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacterBase.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle,
	Run,
	Jump
};

class UPaperFlipbook;
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
	void InputMoveKey(const FInputActionValue& value);
	void InputJumpKey(const FInputActionValue& value);

private:
	void SetState(EPlayerState newState);
	EPlayerState GetState();
	void SetFlipbook();
	void SetSpriteRotation(float value);

private:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* jumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* defaultContext;

	UPROPERTY(EditAnywhere, Category = State)
	EPlayerState state;

	float prevRotationValue;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* idleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* runAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* jumpAnimation;
};
