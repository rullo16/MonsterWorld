// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageBox.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWORLD_1_API UMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMessageText(const FText& Text);

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageBoxText;
};
