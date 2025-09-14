// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "Tank.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> foundTowers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), foundTowers);
	towerCount = foundTowers.Num();

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (playerPawn)
	{
		tankActor = Cast<ATank>(playerPawn);
		if (!tankActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainGameMode.cpp: PlayerPawn is not of type ATank!"));
		}
	}

	int32 loopIndex = 0;
	while (loopIndex < towerCount)
	{
		AActor* towerActor = foundTowers[loopIndex];
		if (towerActor)
		{
			ATower* tower = Cast<ATower>(towerActor);
			if (tower)
			{
				tower->tank = tankActor;
			}
		}

		loopIndex++;
	}


}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
