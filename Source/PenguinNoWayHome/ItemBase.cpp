// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "PlayerCharacterBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	itemID = -1;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionCheck();
}

void AItemBase::CollisionCheck()
{
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FOverlapResult> resultArray;

	bool onCollision = GetWorld()->OverlapMultiByChannel(resultArray,
		GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(10),
		param);

#if ENABLE_DRAW_DEBUG
	FColor	collisionColor = onCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), GetActorLocation(),
		10, 2,
		collisionColor, false, 0.3f);

#endif

	if (onCollision)
	{
		int range = resultArray.Num();

		for (int i = 0; i < range; i++)
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(resultArray[i].GetActor());

			if (IsValid(player) && itemID != -1)
			{
				FItemTable* table = GetItemInfo(itemID);
				EBuffType buffType = table->buffType;
				float value = table->Value;
				float playerHealth = player->GetCurrentHealth();
				float playerFly = player->GetCurrentFly();
				float playerMaxHealth = player->GetMaxHealth();
				float playerMaxFly = player->GetMaxFly();

				switch (buffType)
				{
				case EBuffType::HP:
				{
					float healthValue = (playerHealth + value) >= playerMaxHealth ? playerMaxHealth : (playerHealth + value);
					player->SetCurrentHealth(healthValue);
					Destroy();
					break;
				}
				case EBuffType::FLY:
				{
					float flyValue = (playerFly + value) >= playerMaxFly ? playerMaxFly : (playerFly + value);
					player->SetCurrentFly(flyValue);
					Destroy();
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

FItemTable* AItemBase::GetItemInfo(int ItemID)
{
	if (IsValid(itemTable))
	{
		FItemTable* itemInfo = itemTable->FindRow<FItemTable>(FName(FString::FromInt(itemID)), nullptr);
		return itemInfo;
	}

	return nullptr;
}
