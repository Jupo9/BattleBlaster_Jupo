// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Projectile.h"
#include "NiagaraFunctionLibrary.h"

#include "BasePawn.generated.h"

UCLASS()
class BATTLEBLASTER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

public: 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<AProjectile> projectileClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	UNiagaraSystem* deathParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* deathSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> deathCameraShakeClass;

	void RotateTurret(FVector lookAtTarget);

	void Fire();

	void HandleDestruction();
};
