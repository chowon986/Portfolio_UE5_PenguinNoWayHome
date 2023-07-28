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
	JumpStart,
	Jump,
	JumpEnd,
	FlyStart,
	Fly,
	FlyEnd,
	Death,
};

class UPaperFlipbookComponent;
class UPaperFlipbook;
class UInputAction;
class UInputMappingContext;
UCLASS()
class PENGUINNOWAYHOME_API APlayerCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(APlayerCharacterBase, PlayerHPChangedEvent, float)
	DECLARE_EVENT_OneParam(APlayerCharacterBase, PlayerFlyChangedEvent, float)

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
	void InputFlyKey(const FInputActionValue& value);

private:
	void SetState(EPlayerState newState);
	EPlayerState GetState();
	void SetFlipbook();
	void SetSpriteRotation(float value);

public:
	UFUNCTION()
	void OnFlipbookFinishedPlaying();

	int32 GetMaxHealth() { return maxHealth; }
	float GetCurrentHealth() { return health; }
	int32 GetMaxFly() { return maxFly; }
	float GetCurrentFly() { return fly; }

	void SetCurrentHealth(float value);
	void SetCurrentFly(float value);
	void Death();


private:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* jumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* flyAction;

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
	UPaperFlipbook* jumpStartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* jumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* jumpEndAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* flyStartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* flyAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* flyEndAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* flipbookComponent;

	float maxHealth;
	float health;

	float maxFly;
	float fly;

	float elapsedTime;

	PlayerHPChangedEvent OnPlayerHPChangedEvent;
	PlayerFlyChangedEvent OnPlayerFlyChangedEvent;
	
	bool movable;
};
