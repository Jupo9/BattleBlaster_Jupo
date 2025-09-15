// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	rootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector vectorToTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, vectorToTarget.Rotation().Yaw, 0.f);
	turretMesh->SetWorldRotation(FMath::RInterpTo(turretMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
}

void ABasePawn::Fire()
{
	FVector projectSpawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator projectSpawnRotation = projectileSpawnPoint->GetComponentRotation();

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, projectSpawnLocation, projectSpawnRotation);
	//DrawDebugSphere(GetWorld(), projectSpawnLocation, 25.f, 12, FColor::Red, false, 3.f);
	if (projectile)
	{
		projectile->SetOwner(this);
		AActor* projectileOwner = projectile->GetOwner();
		if (projectileOwner)
		{
			projectileOwner->GetActorNameOrLabel();
		}
	}
}

void ABasePawn::HandleDestruction()
{
	if (deathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), deathParticles, GetActorLocation(), GetActorRotation());
	}
	if (deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetActorLocation());
	}
	if (deathCameraShakeClass)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController)
		{
			playerController->ClientStartCameraShake(deathCameraShakeClass);
		}
	}
}


