// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Display, TEXT("Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Cyan, FString::Printf(TEXT("Hosting")));

	UWorld* world = GetWorld();

	if (!ensure(world != nullptr))
	{
		return;
	}

	world->ServerTravel("/Game/PuzzlePlatforms/Maps/Testing?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& address)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* playerController = GetFirstLocalPlayerController();

	if (!ensure(playerController != nullptr))
	{
		return;
	}

	playerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}