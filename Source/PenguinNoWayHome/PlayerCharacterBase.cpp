// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PaperFlipbookComponent.h"


APlayerCharacterBase::APlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// InputMappingContext 초기화
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> mappingContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/MCPlayerCharacter.MCPlayerCharacter'"));

	if (mappingContext.Succeeded())
		defaultContext = mappingContext.Object;

	// InputAction 초기화
	static ConstructorHelpers::FObjectFinder<UInputAction> inputMoveAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/IAMove.IAMove'"));
		moveAction = inputMoveAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> inputJumpAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/IAJump.IAJump'"));

	if (inputJumpAction.Succeeded())
		jumpAction = inputJumpAction.Object;

	state = EPlayerState::Idle;
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(defaultContext, 0);
		}
	}
}

void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::InputMoveKey);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::InputJumpKey);
	}
}

void APlayerCharacterBase::InputMoveKey(const FInputActionValue& value)
{
	FVector movementVector = value.Get<FVector>();
	AddMovementInput(movementVector, .1f);
	SetState(EPlayerState::Run);
	SetSpriteRotation(movementVector.X);
}

void APlayerCharacterBase::InputJumpKey(const FInputActionValue& value)
{
	Jump();
	SetState(EPlayerState::Jump);
}

void APlayerCharacterBase::SetState(EPlayerState newState)
{
	if (state != newState)
	{
		state = newState;
		SetFlipbook();
	}
}

EPlayerState APlayerCharacterBase::GetState()
{
	return state;
}

void APlayerCharacterBase::SetFlipbook()
{
	switch (state)
	{
	case EPlayerState::Idle:
		GetSprite()->SetFlipbook(idleAnimation);
		break;
	case EPlayerState::Run:
		GetSprite()->SetFlipbook(runAnimation);
		break;
	case EPlayerState::Jump:
		GetSprite()->SetFlipbook(jumpAnimation);
		break;
	default:
		break;
	}
}

void APlayerCharacterBase::SetSpriteRotation(float value)
{
	if (prevRotationValue != value)
	{
		prevRotationValue = value;
		GetSprite()->AddLocalRotation({ 0.f, 180, 0.f });
	}
}
