// Fill out your copyright notice in the Description page of Project Settings.

#include "Red.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Config/InputDataConfig.h"


ARed::ARed()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1000.f;
}

void ARed::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (!InputActions) return;
		
		Input->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &ARed::Move);
	}
}

void ARed::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultInputMapping();



}

void ARed::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	AddMovementInput(FVector(1.f, 0.f, 0.f), Movement.X);
	AddMovementInput(FVector(0.f, 1.f, 0.f), Movement.Y);
}


void ARed::AddDefaultInputMapping()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(TopDownContext, 0);
}


