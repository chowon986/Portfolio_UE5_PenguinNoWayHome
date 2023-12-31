// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "PaperCharacter.h"
#include "NonPlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API ANonPlayerCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	ANonPlayerCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck();
};
