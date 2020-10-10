// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiTPPGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"
#include "PlatformTrigger.h"

UMultiTPPGameInstance::UMultiTPPGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/Blueprints/BP_PlatformTrigger"));
	if (!ensure(PlatformTriggerBPClass.Class != nullptr)) return;

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());
}

void UMultiTPPGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UMultiTPPGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
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

