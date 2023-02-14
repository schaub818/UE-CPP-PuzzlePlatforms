// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Meta=(MakeEditWidget=true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FVector globalTargetLocation;
	FVector globalStartLocation;

	bool movingForward = true;

	UPROPERTY(EditAnywhere)
	int activeTriggers = 1;
};
