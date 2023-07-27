// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterBase.h"
#include "Fan.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API AFan : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	AFan();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck() override;

public:
	float elapsedTime;
	float intervalTime;
};
