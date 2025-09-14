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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* localPlayer = playerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem * subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer))
			{
				subsystem->AddMappingContext(defaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		FHitResult hitResult;
		playerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);

		RotateTurret(hitResult.ImpactPoint);

		/*Draw debug sphere where the cursor is pointing :
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
		needs: #include "DrawDebugHelpers.h" , to work!!!
		*/
	} 
}

void ATank::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	UEnhancedInputComponent* uEIC = CastChecked<UEnhancedInputComponent>(playerInputComponent);
	if (uEIC)
	{
		uEIC->BindAction(moveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);

		uEIC->BindAction(turnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);

		uEIC->BindAction(fireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::MoveInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();

	FVector deltaLocation = FVector(0.f, 0.f, 0.f);

	deltaLocation.X = inputValue * speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::TurnInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();

	FRotator deltaRotation = FRotator(0.f, 0.f, 0.f);

	deltaRotation.Yaw = inputValue * turnSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(deltaRotation, true);
}
