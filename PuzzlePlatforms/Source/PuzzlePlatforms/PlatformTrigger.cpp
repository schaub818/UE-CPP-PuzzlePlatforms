// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(triggerVolume != nullptr))
	{
		return;
	}

	RootComponent = triggerVolume;
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(triggerVolume != nullptr))
	{
		return;
	}

	triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnBeginOverlap);
	triggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnEndOverlap);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated: %s, %s"), *OtherActor->GetFName().ToString(), *OtherComp->GetFName().ToString());
}

void APlatformTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivated: %s, %s"), *OtherActor->GetFName().ToString(), *OtherComp->GetFName().ToString());
}