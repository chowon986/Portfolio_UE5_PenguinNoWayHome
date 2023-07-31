// Fill out your copyright notice in the Description page of Project Settings.


#include "Igloo.h"
#include "PlayerCharacterBase.h"

AIgloo::AIgloo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIgloo::BeginPlay()
{
	Super::BeginPlay();
}

void AIgloo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollisionCheck();
}

void AIgloo::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	FVector collisionLocation = GetActorLocation();

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(30),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), collisionLocation, 30, 10, collisionColor, false, 0.5f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player))
			{
				if (player->GetCurrentHealth() > 0)
				{
					player->SetIsClear(true);
					player->SetMovable(false);
				}
			}
		}
	}
}
