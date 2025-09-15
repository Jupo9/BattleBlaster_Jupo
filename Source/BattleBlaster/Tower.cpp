// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle firetimerHandle;
	GetWorldTimerManager().SetTimer(firetimerHandle, this, &ATower::CkeckFireCondition, fireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isInFireRange())
	{
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::CkeckFireCondition()
{
	if (isInFireRange() && tank->isAlive)
	{
		Fire();
	}
}

bool ATower::isInFireRange()
{
	bool result = false;

	if (tank)
	{
		float distanceToTank = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		result = (distanceToTank <= fireRange);

	}

	return result;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
