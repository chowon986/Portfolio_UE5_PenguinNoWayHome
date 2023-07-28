// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PENGUINNOWAYHOME, Log, All);

#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))

#define	LOG(Format, ...)	UE_LOG(LONGVINTER, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define	LOGSTRING(Str)		UE_LOG(LONGVINTER, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *Str)


UCLASS()
class PENGUINNOWAYHOME_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	HP,
	FLY,
};


USTRUCT(BlueprintType)
struct  FItemTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<EBuffType> buffTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UPaperFlipbook* previewImage;
};

USTRUCT(BlueprintType)
struct  FMonsterTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName monsterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float offensePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UPaperFlipbook* previewImage;
};