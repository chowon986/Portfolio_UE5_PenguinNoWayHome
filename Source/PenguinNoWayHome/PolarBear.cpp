// Fill out your copyright notice in the Description page of Project Settings.


#include "PolarBear.h"
#include "PlayerCharacterBase.h"
#include "PaperFlipbookComponent.h"

APolarBear::APolarBear()
{
	PrimaryActorTick.bCanEverTick = true;
	state = EMonsterState::Idle;

	flipbookComponent = FindComponentByClass<UPaperFlipbookComponent>();
	if (IsValid(flipbookComponent))
	{
		flipbookComponent->OnFinishedPlaying.AddDynamic(this, &APolarBear::OnFlipbookFinishedPlaying);
	}

	elapsedTime = 0.f;
	intervalTime = 2.f;
	attackable = true;
}

void APolarBear::BeginPlay()
{
	Super::BeginPlay();
}

void APolarBear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!flipbookComponent->IsPlaying())
		flipbookComponent->Play();

	elapsedTime += DeltaTime;

	if (elapsedTime > intervalTime)
	{
		CollisionCheck();
		elapsedTime = 0.f;
	}

	if (state == EMonsterState::Attack)
	{
		int32 currentFrame = flipbookComponent->GetPlaybackPositionInFrames();
		if (currentFrame == 2 && attackable)
		{
			TakeDamageCollisionCheck();
			attackable = false;
		}
	}
}

void APolarBear::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector originLocation = GetActorLocation();

	FVector collisionLocation = { originLocation.X + GetActorForwardVector().X * 30.f, originLocation.Y, originLocation.Z - 20.f };

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(20),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), collisionLocation, 20, 10, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player))
				SetState(EMonsterState::Attack);
		}
	}
}

void APolarBear::TakeDamageCollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector originLocation = GetActorLocation();

	FVector collisionLocation = { originLocation.X + GetActorForwardVector().X * 30.f, originLocation.Y, originLocation.Z - 20.f };

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(20),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), collisionLocation, 20, 10, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player))
			{
				float playerHealth = player->GetCurrentHealth();
				float healthValue = (playerHealth - 1.f) >= 0 ? (playerHealth - 1.f) : 0;
				player->SetCurrentHealth(healthValue);
			}
		}
	}
}

void APolarBear::SetState(EMonsterState newState)
{
	if (state != newState)
	{
		state = newState;

		switch (state)
		{
		case EMonsterState::Idle:
			GetSprite()->SetFlipbook(idleAnimation);
			flipbookComponent->SetLooping(true);
			attackable = true;
			break;
		case EMonsterState::Attack:
			GetSprite()->SetFlipbook(attackAnimation);
			flipbookComponent->SetLooping(false);
			break;
		default:
			break;
		}
	}
}

EMonsterState APolarBear::GetState()
{
	return state;
}

void APolarBear::OnFlipbookFinishedPlaying()
{
	if (state == EMonsterState::Attack)
		SetState(EMonsterState::Idle);
}
