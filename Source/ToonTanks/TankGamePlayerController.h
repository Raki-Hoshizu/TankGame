// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void SetPlayerEnabledState(bool bPlayerEnabled);

};
