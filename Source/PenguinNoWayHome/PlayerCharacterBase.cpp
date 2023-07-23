// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


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

	State = EPlayerState::Idle;
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
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Move);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Jump);
	}
}

void APlayerCharacterBase::Move(const FInputActionValue& value)
{
	// AddMovementInput(이동할 방향, 거리)
	FVector movementVector = value.Get<FVector>();
	AddMovementInput(movementVector, .1f);
}

void APlayerCharacterBase::SetState(EPlayerState newState)
{
	if (State != newState)
		State = newState;
}

EPlayerState APlayerCharacterBase::GetState()
{
	return State;
}
