// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOverlay.h"
#include "HUD/MessageBox.h"

void UGameOverlay::SetMessageBoxText(const FText& Text)
{
	if (MessageBox)
	{
		MessageBox->SetMessageText(Text);
	}
}
