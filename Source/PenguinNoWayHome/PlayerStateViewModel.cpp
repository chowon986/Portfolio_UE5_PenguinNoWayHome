// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateViewModel.h"
#include "PlayerCharacterBase.h"

UPlayerStateViewModel::UPlayerStateViewModel()
{
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerController* controller = world->GetFirstPlayerController();
		if (IsValid(controller))
		{
			APlayerCharacterBase* player = Cast<APlayerCharacterBase>(controller->GetCharacter());

			if (IsValid(player))
			{
				player->OnPlayerHPChangedEvent.AddUObject(this, &UPlayerStateViewModel::OnPlayerHPChanged);
				maxHealth = player->GetMaxHealth();
				SetCurrentHealth(player->GetCurrentHealth());
				
				player->OnPlayerFlyChangedEvent.AddUObject(this, &UPlayerStateViewModel::OnPlayerFlyChanged);
				maxFly = player->GetMaxFly();
				SetCurrentFly(player->GetCurrentFly());
			}
		}
	}
}


void UPlayerStateViewModel::SetCurrentHealth(float NewCurrentHealth)
{
	if (currentHealth != NewCurrentHealth)
	{
		UE_MVVM_SET_PROPERTY_VALUE(currentHealth, NewCurrentHealth);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UPlayerStateViewModel::SetCurrentFly(float NewCurrentFly)
{
	if (currentFly != NewCurrentFly)
	{
		UE_MVVM_SET_PROPERTY_VALUE(currentFly, NewCurrentFly);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFlyPercent);
	}
}

void UPlayerStateViewModel::OnPlayerHPChanged(float HP)
{
	SetCurrentHealth(HP);
}


void UPlayerStateViewModel::OnPlayerFlyChanged(float Fly)
{
	SetCurrentFly(Fly);
}