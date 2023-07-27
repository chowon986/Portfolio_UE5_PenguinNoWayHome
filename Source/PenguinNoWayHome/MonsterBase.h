// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NonPlayerCharacterBase.h"
#include "MonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API AMonsterBase : public ANonPlayerCharacterBase
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck();

public:
	UPROPERTY(EditAnywhere, Category = Item)
	UDataTable* monsterTable;
};
