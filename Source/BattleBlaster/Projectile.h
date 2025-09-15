// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Projectile.generated.h"

UCLASS()
class BATTLEBLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* projectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* trailParticles;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* hitParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* launchSound;

	UPROPERTY(EditAnywhere)
	USoundBase* hitSound;

	UPROPERTY(EditAnywhere)
	float damage = 25.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> hitCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
