// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"
#include "PlayerCharacterBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	breakTime = 0.f;
	onceCheck = false;
	moveDirection = "";
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();
}

void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollisionCheck();
}

void ATileBase::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector collisionLocation = GetActorLocation();

	collisionLocation = { collisionLocation.X, collisionLocation.Y, collisionLocation.Z + 10};

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(10),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), collisionLocation, 10, 10, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player) && !onceCheck)
			{
				switch (tileType)
				{
				case ETileType::None:
					break;
				case ETileType::Break:
					onceCheck = true;
					StartBreak();
					break;
				case ETileType::Move:
				{
					if (moveDirection != "")
						MoveTile(moveDirection);
				}
					break;
				case ETileType::Jump:
					player->GetCharacterMovement()->JumpZVelocity = 500.0f;
					player->SetState(EPlayerState::Fly);
					player->Jump();
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		if (startLocation != GetActorLocation())
		{
			float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

			FVector curLocation = GetActorLocation();

			FVector NewLocation = FMath::Lerp(curLocation, startLocation, FMath::Clamp(deltaTime * 5.f, 0.0f, 1.0f));

			SetActorLocation(NewLocation);
		}
	}
}

void ATileBase::StartBreak()
{
	GetWorldTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateUObject(this, &ATileBase::OnTimerExpired), breakTime, false);
}

void ATileBase::OnTimerExpired()
{
	Destroy();
	timerHandle.Invalidate();
}

void ATileBase::MoveTile(FString MoveDirection)
{
	if (MoveDirection == "Down") 
	{
		float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

		FVector curLocation = GetActorLocation();

		float moveSpeed = 10.0f; 
		FVector newLocation = curLocation + FVector(0.f, 0.f, -moveSpeed * deltaTime);

		SetActorLocation(newLocation);
	}
}
