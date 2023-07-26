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

	static ConstructorHelpers::FObjectFinder<UInputAction> inputFlyAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/IAFly.IAFly'"));

	if (inputFlyAction.Succeeded())
		flyAction = inputFlyAction.Object;

	flipbookComponent = FindComponentByClass<UPaperFlipbookComponent>();
	if (IsValid(flipbookComponent))
	{
		flipbookComponent->OnFinishedPlaying.AddDynamic(this, &APlayerCharacterBase::OnFlipbookFinishedPlaying);
	}
	state = EPlayerState::Idle;
	prevRotationValue = 1.f;

	maxHealth = 10.f;
	health = 10.f;

	elapsedTime = 0.f;
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

	elapsedTime += DeltaTime;

	if (elapsedTime > 5.f)
	{
		health -= 1.f;
		elapsedTime = 0.f;

		OnPlayerHPChangedEvent.Broadcast(health);
	}

	UCharacterMovementComponent* movement = GetCharacterMovement();
	if (movement)
	{
		bool isMoving = movement->Velocity.Size() != 0;
		if (!isMoving)
		{
			if (state != EPlayerState::JumpStart &&
				state != EPlayerState::Jump &&
				state != EPlayerState::JumpEnd &&
				state != EPlayerState::FlyStart &&
				state != EPlayerState::Fly &&
				state != EPlayerState::FlyEnd)
				SetState(EPlayerState::Idle);
		}

		if (state == EPlayerState::Jump && !movement->IsFalling())
			SetState(EPlayerState::JumpEnd);

		else if (state == EPlayerState::Fly && !movement->IsFalling())
			SetState(EPlayerState::FlyEnd);
	}

	if (!flipbookComponent->IsPlaying())
		flipbookComponent->Play();
}

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::InputMoveKey);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &APlayerCharacterBase::InputJumpKey);
		enhancedInputComponent->BindAction(flyAction, ETriggerEvent::Started, this, &APlayerCharacterBase::InputFlyKey);
	}
}

void APlayerCharacterBase::InputMoveKey(const FInputActionValue& value)
{
	FVector movementVector = value.Get<FVector>();
	AddMovementInput(movementVector, .1f);

	if (state != EPlayerState::JumpStart &&
		state != EPlayerState::Jump &&
		state != EPlayerState::FlyStart &&
		state != EPlayerState::Fly)
	{
		SetState(EPlayerState::Run);
	}
	SetSpriteRotation(movementVector.X);
}

void APlayerCharacterBase::InputJumpKey(const FInputActionValue& value)
{
 	SetState(EPlayerState::JumpStart);
	Jump();
}

void APlayerCharacterBase::InputFlyKey(const FInputActionValue& value)
{
	SetState(EPlayerState::FlyStart);
	Jump();
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
		flipbookComponent->SetLooping(true);
		break;
	case EPlayerState::Run:
		GetSprite()->SetFlipbook(runAnimation);
		flipbookComponent->SetLooping(true);
		break;
	case EPlayerState::JumpStart:
		GetSprite()->SetFlipbook(jumpStartAnimation);
		flipbookComponent->SetLooping(false);
		break;
	case EPlayerState::Jump:
		GetSprite()->SetFlipbook(jumpAnimation);
		flipbookComponent->SetLooping(true);
		break;
	case EPlayerState::JumpEnd:
		GetSprite()->SetFlipbook(jumpEndAnimation);
		flipbookComponent->SetLooping(false);
		break;
	case EPlayerState::FlyStart:
		GetSprite()->SetFlipbook(flyStartAnimation);
		flipbookComponent->SetLooping(false);
		break;
	case EPlayerState::Fly:
		GetSprite()->SetFlipbook(flyAnimation);
		flipbookComponent->SetLooping(true);
		break;
	case EPlayerState::FlyEnd:
		GetSprite()->SetFlipbook(flyEndAnimation);
		flipbookComponent->SetLooping(false);
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

void APlayerCharacterBase::OnFlipbookFinishedPlaying()
{
	if (state == EPlayerState::JumpStart)
		SetState(EPlayerState::Jump);

	else if (state == EPlayerState::FlyStart)
		SetState(EPlayerState::Fly);

	else if (state == EPlayerState::JumpEnd || state == EPlayerState::FlyEnd)
		SetState(EPlayerState::Idle);
}