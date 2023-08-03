// Fill out your copyright notice in the Description page of Project Settings.


#include "Fan.h"
#include "PlayerCharacterBase.h"

AFan::AFan()
{
	PrimaryActorTick.bCanEverTick = true;

	elapsedTime = 0.f;
	intervalTime = 0.f;
}

void AFan::BeginPlay()
{
	Super::BeginPlay();
}

void AFan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime += DeltaTime;

	if (elapsedTime > intervalTime)
	{
		elapsedTime = 0.f;
		CollisionCheck();
	}
}

void AFan::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector originLocation = GetActorLocation();

	FVector collisionLocation = { originLocation.X + GetActorForwardVector().X * 40.f, originLocation.Y, originLocation.Z};
	
	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeBox(FVector({ 35, 32, 32 })),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;
	FVector extent = FVector({ 35, 32, 32 });

	DrawDebugBox(GetWorld(), collisionLocation, extent, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player))
			{
				double PushDirection = (player->GetActorLocation().X - GetActorLocation().X) > 0.f ? 1.f : -1.f;

				float InterpSpeed = 1.0f; 
				FVector TargetLocation = { player->GetActorLocation().X + (PushDirection * 50), player->GetActorLocation().Y, player->GetActorLocation().Z }; // 조정 가능한 이동 거리
				FVector NewLocation = FMath::Lerp(player->GetActorLocation(), TargetLocation, InterpSpeed * GetWorld()->DeltaTimeSeconds);
				player->SetActorLocation(NewLocation);

			}
		}
	}
}
