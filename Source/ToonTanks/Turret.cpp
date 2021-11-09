// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
		RotateTurret(Tank->GetActorLocation());
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATurret::CheckFireCondition()
{
	if (Tank == nullptr) return;
	if (InFireRange() && Tank->bAlive)
		Fire();
}

bool ATurret::InFireRange()
{
	if (Tank)
		return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
	return false;
}