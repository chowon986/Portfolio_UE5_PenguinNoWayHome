// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
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
	void StartBreak();
	void OnTimerExpired();
	void MoveTile(FString MoveDirection);

public:
	UPROPERTY(EditAnywhere, Category = State)
	ETileType tileType;

	FTimerHandle timerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BreakTile)
	float breakTime;

	bool onceCheck;

	FVector startLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveTile)
	FString moveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveTile)
	float moveSpeed;
};
