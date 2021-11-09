// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "TankGamePlayerController.h"

void ATankGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankGamePlayerController)
			TankGamePlayerController->SetPlayerEnabledState(false);
		GameOver(false);
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
		UE_LOG(LogTemp, Warning, TEXT("%i"), TargetTurrets);
		if (TargetTurrets <= 0)
			GameOver(true);
	}
}

void ATankGameGameMode::HandleGameStart()
{
	TargetTurrets = GetTargetTurretsCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankGamePlayerController = Cast<ATankGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (TankGamePlayerController)
	{
		TankGamePlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(TankGamePlayerController, &ATankGamePlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 ATankGameGameMode::GetTargetTurretsCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}