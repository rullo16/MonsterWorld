// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MessageBox.h"
#include "Components/TextBlock.h"


void UMessageBox::SetMessageText(const FText& Text)
{
	if (MessageBoxText)
	{
		MessageBoxText->SetText(Text);
	}
}
