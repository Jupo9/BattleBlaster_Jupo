// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* defaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* turnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* fireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnSpeed = 50.f;

	void MoveInput(const FInputActionValue& value);
	void TurnInput(const FInputActionValue& value);
};
