// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "NonPlayerCharacterBase.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API AItemBase : public ANonPlayerCharacterBase
{
	GENERATED_BODY()

public:
	AItemBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck() override;
	FItemTable* GetItemInfo(int itemID);

public:
	UPROPERTY(EditAnywhere, Category = Item)
	int itemID;

	UPROPERTY(EditAnywhere, Category = Item)
	UDataTable* itemTable;
};
