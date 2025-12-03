// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Green.generated.h"


class UBoxComponent;

UCLASS()
class MONSTERWORLD_1_API AGreen : public APaperCharacter
{
	GENERATED_BODY()

public:
	AGreen();

	FORCEINLINE FString GetMessageText() const { return Dialogue; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties)
	FString Dialogue; 

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
};
