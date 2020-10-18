// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	GetStaticMeshComponent()->SetSimulatePhysics(false);
	GetStaticMeshComponent()->SetEnableGravity(false);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	PlatformSpeed = 10.0f;

	if (HasAuthority())
	{
		bMovingBack = false;
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}
	
	ActiveTriggers > 0 ? bIsActive = true : bIsActive = false;
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (HasAuthority() && bIsActive)
	{
		FVector Location = GetActorLocation();
		FVector Direction = bMovingBack ? GlobalStartLocation - GlobalTargetLocation : GlobalTargetLocation - GlobalStartLocation;
		Direction.Normalize();
		Location += DeltaSeconds * PlatformSpeed * Direction;
		SetActorLocation(Location);
		
		if (Location.Equals(GlobalTargetLocation, 5.0f))
		{
			bMovingBack = true;
		}
		else if (Location.Equals(GlobalStartLocation, 5.0f))
		{
			bMovingBack = false;
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
	bIsActive = true;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers--;
	if (ActiveTriggers <= 0)
		bIsActive = false;
}
