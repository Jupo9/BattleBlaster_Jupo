// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Tank.h"
#include "ScreenMessage.h"

#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> screenMessageClass;

	UScreenMessage* screenMessageWidget;

	UPROPERTY(EditAnywhere)
	float gameOverDelay = 1.5f;

	UPROPERTY(EditAnywhere)
	int32 countdownDelay = 4;

	int32 countdownSeconds;

	FTimerHandle countdownTimerHandle;

	bool isVictory = false;

	ATank* tankActor;
	int32 towerCount;

	void ActorDied(AActor* deadActor);

	void OnGameOverTimerTimeout();
	void OnCountdownTimerTimeout();
};
