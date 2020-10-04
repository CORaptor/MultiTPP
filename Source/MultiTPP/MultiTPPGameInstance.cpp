// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiTPPGameInstance.h"

UMultiTPPGameInstance::UMultiTPPGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructor"));
}

void UMultiTPPGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UMultiTPPGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UMultiTPPGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Init"));
}
