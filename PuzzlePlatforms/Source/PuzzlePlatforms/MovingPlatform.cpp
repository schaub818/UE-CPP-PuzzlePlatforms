// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Math/UnrealMathUtility.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		globalStartLocation = GetActorLocation();
		globalTargetLocation = TargetLocation + globalStartLocation;
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	activeTriggers++;

	GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Triggers: %i"), activeTriggers));
}

void AMovingPlatform::RemoveActiveTrigger()
{
	activeTriggers = FMath::Clamp(--activeTriggers, 0, 1000);

	GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Triggers: %i"), activeTriggers));
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && activeTriggers > 0)
	{
		FVector currentLocation = GetActorLocation();
		FVector target;
		FVector newLocation;

		if (movingForward)
		{
			target = globalTargetLocation;
		}
		else
		{
			target = globalStartLocation;
		}

		if ((currentLocation - target).Size() < MoveSpeed * DeltaTime)
		{
			newLocation = target;
			movingForward = !movingForward;
		}
		else
		{
			newLocation = FMath::VInterpConstantTo(currentLocation, target, DeltaTime, MoveSpeed);
		}

		SetActorLocation(newLocation);
	}
}