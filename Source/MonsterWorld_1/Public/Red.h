// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Red.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputDataConfig;

UCLASS()
class MONSTERWORLD_1_API ARed : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	ARed();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* TopDownContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputDataConfig* InputActions;


	void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;


	void AddDefaultInputMapping();



};
