// Fill out your copyright notice in the Description page of Project Settings.

#include "Red.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Config/InputDataConfig.h"
#include "PaperFlipbookComponent.h"
#include "HUD/GameHUD.h"
#include "HUD/GameOverlay.h"
#include "HUD/MessageBox.h"
#include "Components/BoxComponent.h"
#include "Items/Pickup.h"
#include "Green.h"


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

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(GetRootComponent());
}

void ARed::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (!InputActions) return;
		
		Input->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &ARed::Move, false);
		Input->BindAction(InputActions->Move, ETriggerEvent::Completed, this, &ARed::Move, true);
		Input->BindAction(InputActions->Interact, ETriggerEvent::Triggered, this, &ARed::Interact);
	}
}

void ARed::SetOverlappingItem(APickup* Item)
{
	OverlappingItem = Item;
}

void ARed::SetOverlappingCharacter(AGreen* Character)
{
	OverlappingCharacter = Character;
}

void ARed::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultInputMapping();
	InitializeDefaultHUD();


}

void ARed::Move(const FInputActionValue& Value, const bool TransitionToIdle)
{	
	if (Value.Get<FVector2D>().X != 0.f || Value.Get<FVector2D>().Y != 0.f) {
		Movement = Value.Get<FVector2D>();
	}

	UpdateAnimation(TransitionToIdle);

	AddMovementInput(FVector(1.f, 0.f, 0.f), Movement.X);
	AddMovementInput(FVector(0.f, 1.f, 0.f), Movement.Y);
}

void ARed::Interact()
{
	if (OverlappingItem)
	{
		MessageText = OverlappingItem->GetMessageText();
		if (GameOverlay)
		{
			UE_LOG(LogTemp, Warning, TEXT("Showing Message Box"));
			UMessageBox* MessageBox = Cast<UMessageBox>(GameOverlay->GetMessageBox());
			if (MessageBox)
			{	
				MessageBox->SetMessageText(FText::FromString(MessageText));
				MessageBox->SetVisibility(ESlateVisibility::Visible);

				// Local timer handle and delegate for the lambda callback
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([MessageBox]()
				{
					if (MessageBox)
					{
						MessageBox->SetVisibility(ESlateVisibility::Hidden);
					}
				});

				if (UWorld* World = GetWorld())
				{
					World->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.0f, false);
				}
				
			}
		}
		OverlappingItem->Destroy();
	}

	if (OverlappingCharacter)
	{
		MessageText = OverlappingCharacter->GetMessageText();
		if (GameOverlay)
		{
			UE_LOG(LogTemp, Warning, TEXT("Showing Message Box"));
			UMessageBox* MessageBox = Cast<UMessageBox>(GameOverlay->GetMessageBox());
			if (MessageBox)
			{
				MessageBox->SetMessageText(FText::FromString(MessageText));
				MessageBox->SetVisibility(ESlateVisibility::Visible);

				// Local timer handle and delegate for the lambda callback
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([MessageBox]()
					{
						if (MessageBox)
						{
							MessageBox->SetVisibility(ESlateVisibility::Hidden);
						}
					});

				if (UWorld* World = GetWorld())
				{
					World->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.0f, false);
				}

			}
		}
	}
}

void ARed::UpdateAnimation(const bool TransitionToIdle)
{
	if (TransitionToIdle)

	{
		if (Movement.X > 0.f)
		{
			GetSprite()->SetFlipbook(IdleAnimationRight);
		}
		else if (Movement.X < 0.f)
		{
			GetSprite()->SetFlipbook(IdleAnimationLeft);
		}
		else if (Movement.Y > 0.f)
		{
			GetSprite()->SetFlipbook(IdleAnimationDown);
		}
		else if (Movement.Y < 0.f)
		{
			GetSprite()->SetFlipbook(IdleAnimationUp);
		}
	}
	else 
	{
		if (Movement.X > 0.f)
		{
			GetSprite()->SetFlipbook(WalkAnimationRight);
		}
		else if (Movement.X < 0.f)
		{
			GetSprite()->SetFlipbook(WalkAnimationLeft);
		}
		else if (Movement.Y > 0.f)
		{
			GetSprite()->SetFlipbook(WalkAnimationDown);
		}
		else if (Movement.Y < 0.f)
		{
			GetSprite()->SetFlipbook(WalkAnimationUp);
		}
	}
}


void ARed::AddDefaultInputMapping()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(TopDownContext, 0);
}

void ARed::InitializeDefaultHUD()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());
		if (GameHUD)
		{
			GameOverlay = GameHUD->GetGameOverlay();
			if (GameOverlay)
			{
				GameOverlay->SetMessageBoxText(FText::FromString("You Picked Up a Health Potion!"));
				UMessageBox* MessageBox = Cast<UMessageBox>(GameOverlay->GetMessageBox());
				if (MessageBox)
				{
					MessageBox->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}


