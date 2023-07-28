// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "MonsterBase.h"
#include "PolarBear.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Attack,
};

class UPaperFlipbook;
class UPaperFlipbookComponent;
UCLASS()
class PENGUINNOWAYHOME_API APolarBear : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	APolarBear();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck() override;
	void TakeDamageCollisionCheck();

	void SetState(EMonsterState newState);
	EMonsterState GetState();

	UFUNCTION()
		void OnFlipbookFinishedPlaying();

public:
	EMonsterState state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* idleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* attackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* flipbookComponent;

	float elapsedTime;
	float intervalTime;
	bool attackable;
};
