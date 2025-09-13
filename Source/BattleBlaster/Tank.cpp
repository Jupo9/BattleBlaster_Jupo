// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(rootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	playerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	playerInputComponent->BindAxis("Turn", this, &ATank::Turn);
}

void ATank::Move(float value)
{
	FVector deltaLocation = FVector::ZeroVector;

	deltaLocation.X = value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;

	deltaRotation.Yaw = value * turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(deltaRotation, true);
}