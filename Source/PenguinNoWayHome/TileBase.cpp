// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"
#include "PlayerCharacterBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
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

			if (IsValid(player))
			{
				switch (tileType)
				{
				case ETileType::None:
					break;
				case ETileType::Break:					
					Destroy();
					break;
				case ETileType::Move:
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
}
