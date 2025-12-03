// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickup.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/PickupInterface.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	Sprite->SetupAttachment(GetRootComponent());
	RootComponent = Sprite;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBoxOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APickup::OnBoxEndOverlap);

	MessageText = FString::Printf(TEXT("You picked up: %s"), *ItemName);
	
}

void APickup::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with pickup: %s"), *GetName());
		PickupInterface->SetOverlappingItem(this);
	}
}

void APickup::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}
}




// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

