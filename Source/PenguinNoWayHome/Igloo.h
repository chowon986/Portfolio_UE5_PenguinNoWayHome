// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "NonPlayerCharacterBase.h"
#include "Igloo.generated.h"

/**
 * 
 */
UCLASS()
class PENGUINNOWAYHOME_API AIgloo : public ANonPlayerCharacterBase
{
	GENERATED_BODY()
	
public:
	AIgloo();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CollisionCheck();
	void OnTimerExpired();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAudioComponent* audioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* clear;

	FTimerHandle timerHandle;
	bool onceCheck;
};
