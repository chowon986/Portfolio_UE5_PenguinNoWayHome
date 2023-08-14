// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpButtonBase.h"
#include "PlayerCharacterBase.h"
#include "PlayerCharacterController.h"

void UJumpButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	jumpButton = Cast<UButton>(GetWidgetFromName("JumpButton"));
	if (IsValid(jumpButton))
		jumpButton->OnClicked.AddDynamic(this, &UJumpButtonBase::ClickJumpButton);
}

void UJumpButtonBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void UJumpButtonBase::ClickJumpButton()
{
	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));

	if (IsValid(controller))
	{
		APlayerCharacterBase* player = Cast<APlayerCharacterBase>(controller->GetCharacter());
		if(IsValid(player))
			player->ClickJumpButton();
	}
}
