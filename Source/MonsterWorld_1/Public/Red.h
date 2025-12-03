// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Interfaces/PickupInterface.h"
#include "Interfaces/DialogueInterface.h"
#include "Red.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputDataConfig;
class UPaperFlipbook;
class UGameOverlay;
class UBoxComponent;
class APickup;
class AGreen;

UCLASS()
class MONSTERWORLD_1_API ARed : public APaperCharacter, public IPickupInterface
{
	GENERATED_BODY()
	
public:
	ARed();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetOverlappingItem(APickup* Item) override;
	virtual void SetOverlappingCharacter(AGreen* Character);
protected:

	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* TopDownContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputDataConfig* InputActions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Animation)
	UPaperFlipbook* IdleAnimationDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* IdleAnimationUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* IdleAnimationLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* IdleAnimationRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* WalkAnimationDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* WalkAnimationUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* WalkAnimationLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* WalkAnimationRight;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* InteractionBox;


	void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value, const bool TransitionToIdle);

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void UpdateAnimation(const bool TransitionToIdle);

	

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly)
	APickup* OverlappingItem;

	UPROPERTY(VisibleInstanceOnly)
	AGreen* OverlappingCharacter;

	FVector2D Movement;
	UGameOverlay* GameOverlay;
	FString MessageText;

	void AddDefaultInputMapping();
	void InitializeDefaultHUD();


};
