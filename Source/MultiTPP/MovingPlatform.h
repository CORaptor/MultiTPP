// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void AddActiveTrigger();

	void RemoveActiveTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PlatformSpeed;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;
private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	bool bMovingBack;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

	bool bIsActive;
};
