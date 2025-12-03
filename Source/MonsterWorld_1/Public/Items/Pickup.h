// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class MONSTERWORLD_1_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	FORCEINLINE FString GetItemName() const { return ItemName; }
	FORCEINLINE FString GetMessageText() const { return MessageText; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Properties)
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties)
	FString MessageText;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
