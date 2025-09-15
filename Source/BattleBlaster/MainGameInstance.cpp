// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMainGameInstance::ChangeLevel(int32 index)
{
	if (index > 0 && index <= lastLevelIndex)
	{
		currentLevelIndex = index;

		FString levelNameString = FString::Printf(TEXT("Level_%d"), currentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *levelNameString);
	}
}

void UMainGameInstance::LoadNextLevel()
{
	if (currentLevelIndex < lastLevelIndex)
	{
		ChangeLevel(currentLevelIndex + 1);
	}
	else
	{
		RestartGame();
	}
}

void UMainGameInstance::RestartCurrentLevel()
{
	ChangeLevel(currentLevelIndex);
}

void UMainGameInstance::RestartGame()
{
	ChangeLevel(1);
}
