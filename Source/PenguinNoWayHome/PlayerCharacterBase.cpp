// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PaperFlipbookComponent.h"
#include "PlayerCharacterController.h"


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

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	if (inputFlyAction.Succeeded())
		flyAction = inputFlyAction.Object;

	flipbookComponent = FindComponentByClass<UPaperFlipbookComponent>();
	if (IsValid(flipbookComponent))
	{
		flipbookComponent->OnFinishedPlaying.AddDynamic(this, &APlayerCharacterBase::OnFlipbookFinishedPlaying);
	}
	state = EPlayerState::Idle;
	prevRotationValue = 1.f;

	maxHealth = 100;
	health = 30;

	maxFly = 10.f;
	fly = 5.f;

	elapsedTime = 0.f;
	movable = true;

	prevDirection = "Right";
	direction = "Right";

	//FString stringHealth = FString::FromInt(health);
	//
	//LOG(TEXT("Player Health: %d"), health);

	//FString message = TEXT("This is a log message!");
	//LOGSTRING(message);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->bIsUISound = true;
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (joystick)
			playerController->ActivateTouchInterface(joystick);

		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(defaultContext, 0);
		}
	}

	FVector playerLocation = GetTransform().GetLocation();
	cameraComponent->SetAbsolute(true);
	cameraComponent->SetWorldLocation({ 32 * 5.5f, playerLocation.Y + 1000.f, playerLocation.Z });
	cameraComponent->SetWorldRotation(FRotator(0, -90, 0));
}

void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cameraComponent)
	{
		FVector cameraLocation = cameraComponent->GetComponentLocation();
		FVector newCameraLocation = { cameraLocation.X , cameraLocation.Y, GetTransform().GetLocation().Z };
		cameraComponent->SetWorldLocation(newCameraLocation);
	}

	if (state == EPlayerState::Death)
	{
		FVector curLocation = GetActorLocation();
		if (curLocation.Z < 0.f)
			Destroy();
	}
	else
		CollisionCheck();
		

	if(state != EPlayerState::Death)
		elapsedTime += DeltaTime;

	if (elapsedTime > 2.f && isClear == false)
	{
		SetCurrentHealth(health - 2);
		OnPlayerHPChangedEvent.Broadcast(health);
		elapsedTime = 0.f;
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
				state != EPlayerState::FlyEnd &&
				state != EPlayerState::Death)
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
		enhancedInputComponent->BindAction(flyAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::InputFlyKey);
	}
}

void APlayerCharacterBase::InputMoveKey(const FInputActionValue& value)
{
	if (movable)
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

		// LOG(TEXT("CurMovementVectorX: %f"), movementVector.X);

		if (movementVector.X > 0)
			direction = "Right";
		else
			direction = "Left";

		if (direction != prevDirection)
		{
			prevDirection = direction;
			SetSpriteRotation(movementVector.X);
		}
	}
}

void APlayerCharacterBase::InputJumpKey(const FInputActionValue& value)
{
	if (movable)
	{
		if (state == EPlayerState::Idle || state == EPlayerState::Run || state == EPlayerState::JumpEnd)
		{
			GetCharacterMovement()->JumpZVelocity = 300.0f;
			SetState(EPlayerState::JumpStart);
			Jump();
		}
	}
}

void APlayerCharacterBase::InputFlyKey(const FInputActionValue& value)
{
	if (movable)
	{
		if (state == EPlayerState::Idle || state == EPlayerState::Run || state == EPlayerState::JumpEnd)
		{
			if (fly > 0)
			{
				SetCurrentFly(fly - 0.2f);
				GetCharacterMovement()->JumpZVelocity = 200.0f;
				SetState(EPlayerState::FlyStart);
				Jump();
			}
		}
		else if (state == EPlayerState::Fly)
		{
			if (fly > 0)
			{
				SetCurrentFly(fly - 0.2f);
				fly -= 0.2f;
				Jump();
			}
		}
	}
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
	case EPlayerState::Death:
		Death();
		GetSprite()->SetFlipbook(idleAnimation);
		flipbookComponent->SetLooping(true);
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

void APlayerCharacterBase::SetCurrentHealth(float value)
{	
	//health = value;
	//OnPlayerHPChangedEvent.Broadcast(health);
}

void APlayerCharacterBase::SetCurrentFly(float value)
{
	fly = value;
	OnPlayerFlyChangedEvent.Broadcast(fly);
}

void APlayerCharacterBase::Death()
{
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	Jump();

	FRotator CurrentRotation = GetSprite()->GetRelativeRotation();
	FRotator NewRotation = FRotator(180.0f, CurrentRotation.Yaw, CurrentRotation.Roll);

	GetSprite()->SetRelativeRotation(NewRotation);
	AddLocationY(100.f);
}

void APlayerCharacterBase::SetMovable(bool value)
{
	movable = value;
}

void APlayerCharacterBase::AddLocationY(float value)
{
	FVector curLocation = GetActorLocation();

	SetActorLocation({ curLocation.X, curLocation.Y + value, curLocation.Z });
}

void APlayerCharacterBase::SetLocationYtoZero()
{
	FVector curLocation = GetActorLocation();

	SetActorLocation({ curLocation.X, 0, curLocation.Z });
}

void APlayerCharacterBase::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector collisionLocation = GetActorLocation();

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(14),
		param);

//#if ENABLE_DRAW_DEBUG
//	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;
//
//	DrawDebugSphere(GetWorld(), collisionLocation, 14, 3, collisionColor, false, 0.5f);
//
//#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			FString actorLabel = resultArray[i].GetActor()->GetActorLabel();
			if (actorLabel == "Plane" && GetActorLocation().Y != 0)
				SetLocationYtoZero();
		}
	}
}

void APlayerCharacterBase::SetSound()
{
	audioComponent->SetSound(itemSoundBase);
	audioComponent->Play();
}

void APlayerCharacterBase::ClickJumpButton()
{
	if (movable)
	{
		if (state == EPlayerState::Idle || state == EPlayerState::Run || state == EPlayerState::JumpEnd)
		{
			GetCharacterMovement()->JumpZVelocity = 300.0f;
			SetState(EPlayerState::JumpStart);
			Jump();
		}
	}
}
