// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayerCharacterBase.h"
#include "TileBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETileType : uint8
{
	None,
	Break,
	Move,
	Jump,
};

UCLASS()
class PENGUINNOWAYHOME_API ATileBase : public ANonPlayerCharacterBase
{
	GENERATED_BODY()
	

public:
	ATileBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck();

public:
	UPROPERTY(EditAnywhere, Category = State)
	ETileType tileType;
};
