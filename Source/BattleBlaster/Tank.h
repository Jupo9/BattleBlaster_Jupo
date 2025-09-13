// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
*
*/
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnSpeed = 50.f;

	void Move(float value);

	void Turn(float value);
};
