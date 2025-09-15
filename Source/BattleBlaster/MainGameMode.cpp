// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "Tank.h"
#include "MainGameInstance.h"

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

	countdownSeconds = countdownDelay;
	GetWorldTimerManager().SetTimer(countdownTimerHandle, this, &AMainGameMode::OnCountdownTimerTimeout, 1.f, true);
}

void AMainGameMode::OnCountdownTimerTimeout()
{
	countdownSeconds -= 1;

	if (countdownSeconds > 0)
	{

	}
	else if (countdownSeconds == 0)
	{
		tankActor->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(countdownTimerHandle);
	}

}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainGameMode::ActorDied(AActor* deadActor)
{
	bool isGameOver = false;

	if (deadActor == tankActor)
	{
		tankActor->HandleDestruction();
		isGameOver = true;
	}
	else
	{
		ATower* deadTower = Cast<ATower>(deadActor);
		if (deadTower)
		{
			deadTower->HandleDestruction();

			towerCount--;
			if (towerCount <= 0)
			{
				isGameOver = true;
				isVictory = true;
			}
		}
	}

	if (isGameOver)
	{
		FString gameOverString = isVictory ? "Victory!" : "Defeat!";

		FTimerHandle gameOverTimerHandle;
		GetWorldTimerManager().SetTimer(gameOverTimerHandle, this, &AMainGameMode::OnGameOverTimerTimeout, gameOverDelay, false);
	}
}

void AMainGameMode::OnGameOverTimerTimeout()
{
	UGameInstance* gameInstance = GetGameInstance();
	if (gameInstance)
	{
		UMainGameInstance* mainGameInstance = Cast<UMainGameInstance>(gameInstance);
		if (mainGameInstance)
		{
			if (isVictory)
			{
				mainGameInstance->LoadNextLevel();
			}
			else
			{
				mainGameInstance->RestartCurrentLevel();
			}
		}
	}
}
