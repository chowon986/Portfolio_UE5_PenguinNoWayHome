// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayerCharacterBase.h"

ANonPlayerCharacterBase::ANonPlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANonPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANonPlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANonPlayerCharacterBase::CollisionCheck()
{
}