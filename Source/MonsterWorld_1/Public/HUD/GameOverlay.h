// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWORLD_1_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UPROPERTY(meta = (BindWidget))
	class UMessageBox* MessageBox;

public:

	void SetMessageBoxText(const FText& Text);
	FORCEINLINE UMessageBox* GetMessageBox() const { return MessageBox; }
};
