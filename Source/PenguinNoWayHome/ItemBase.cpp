// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "PlayerCharacterBase.h"
#include "PlayerCharacterController.h"

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
		ECC_GameTraceChannel1,
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
				TArray<EBuffType> buffType = table->buffTypes;
				int buffTypeSize = buffType.Num();
				float value = table->Value;
				float playerHealth = player->GetCurrentHealth();
				float playerFly = player->GetCurrentFly();
				float playerMaxHealth = player->GetMaxHealth();
				float playerMaxFly = player->GetMaxFly();

				for (int j = 0; j < buffTypeSize; j++)
				{
					if (buffType[j] == EBuffType::HP)
					{
						float healthValue = (playerHealth + value) >= playerMaxHealth ? playerMaxHealth : (playerHealth + value);
						player->SetCurrentHealth(healthValue);

						APlayerCharacterController* controller = Cast<APlayerCharacterController>(player->GetController());
						if (IsValid(controller))
						{
							if(controller->OnSound())
								player->SetSound();
						}
					}
				}

				Destroy();
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
