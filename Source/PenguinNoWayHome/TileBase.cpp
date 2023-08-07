// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"
#include "PlayerCharacterBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	breakTime = 0.5f;
	onceCheck = false;
	moveDirection = "";
	moveSpeed = 10.f;
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
	param.AddIgnoredActor(ECC_GameTraceChannel7);

	TArray<FOverlapResult> resultArray;

	FVector collisionLocation = GetActorLocation();

	collisionLocation = { collisionLocation.X, collisionLocation.Y, collisionLocation.Z + 4};

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeBox(FVector({14, 32, 20})),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;
	FVector extent = FVector({ 14, 32, 20 });

	DrawDebugBox(GetWorld(), collisionLocation, extent, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		if (range < 2)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[0].GetActor());

			if (tileType == ETileType::Break && !onceCheck)
			{
				onceCheck = true;
				StartBreak();
			}
			else if (tileType == ETileType::Move)
			{
				if (IsValid(player))
					MoveTile(moveDirection);
				else if (startLocation != GetActorLocation())
				{
					float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

					FVector curLocation = GetActorLocation();

					FVector NewLocation = FMath::Lerp(curLocation, startLocation, FMath::Clamp(deltaTime * 5.f, 0.0f, 1.0f));

					SetActorLocation(NewLocation);
				}
			}
			else if (tileType == ETileType::Jump)
			{
				if (IsValid(player))
				{
					player->GetCharacterMovement()->JumpZVelocity = 500.0f;
					player->SetState(EPlayerState::Fly);
					player->Jump();
				}

			}
		}
	}
	else if (startLocation != GetActorLocation() && tileType == ETileType::Move)
	{
		float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

		FVector curLocation = GetActorLocation();

		FVector NewLocation = FMath::Lerp(curLocation, startLocation, FMath::Clamp(deltaTime * 5.f, 0.0f, 1.0f));

		SetActorLocation(NewLocation);
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
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector curLocation = GetActorLocation();
	
	if (MoveDirection == "Down")
	{
		FVector newLocation = curLocation + FVector(0.f, 0.f, -moveSpeed * deltaTime);

		SetActorLocation(newLocation);
	}
	else if (MoveDirection == "Right")
	{
		FVector newLocation = curLocation + FVector(moveSpeed * deltaTime, 0.f, 0.f);

		SetActorLocation(newLocation);
	}
	else if (MoveDirection == "Left")
	{
		FVector newLocation = curLocation + FVector(-moveSpeed * deltaTime, 0.f, 0.f);

		SetActorLocation(newLocation);
	}
	else if (MoveDirection == "Up")
	{
		FVector newLocation = curLocation + FVector(0.f, 0.f, moveSpeed * deltaTime);

		SetActorLocation(newLocation);
	}
}
