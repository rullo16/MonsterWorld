// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDialogueInterface : public UInterface
{
	GENERATED_BODY()
};


class MONSTERWORLD_1_API IDialogueInterface
{
	GENERATED_BODY()
	

public:

	virtual void SetOverlappingCharacter(class AGreen* Character);

};
