// Fill out your copyright notice in the Description page of Project Settings.


#include "Igloo.h"
#include "PlayerCharacterBase.h"

AIgloo::AIgloo()
{
	PrimaryActorTick.bCanEverTick = true;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->bIsUISound = true;

	onceCheck = false;
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

	collisionLocation = { collisionLocation.X, collisionLocation.Y + 10, collisionLocation.Z};

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		collisionLocation, FQuat::Identity,
		ECC_GameTraceChannel4,
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
				if (player->GetCurrentHealth() > 0 && !onceCheck)
				{
					onceCheck = true;
					player->SetIsClear(true);
					player->SetMovable(false);
					audioComponent->SetSound(clear);
					audioComponent->Play();
					GetWorldTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateUObject(this, &AIgloo::OnTimerExpired), 3.5f, false);
				}
			}
		}
	}
}

void AIgloo::OnTimerExpired()
{
	UGameplayStatics::OpenLevel(this, "TitleLevel");
}
