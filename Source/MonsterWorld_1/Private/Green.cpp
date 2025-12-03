// Fill out your copyright notice in the Description page of Project Settings.


#include "Green.h"
#include "Interfaces/PickupInterface.h"
#include "Components/BoxComponent.h"



AGreen::AGreen()
{
	Dialogue = "Welcome To this town";

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
}

void AGreen::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGreen::OnBoxOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGreen::OnBoxEndOverlap);


	Dialogue = "Welcome To this town";
}

void AGreen::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping"));

	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with Green"));
		PickupInterface->SetOverlappingCharacter(this);
	}
}

void AGreen::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingCharacter(nullptr);
	}
}
