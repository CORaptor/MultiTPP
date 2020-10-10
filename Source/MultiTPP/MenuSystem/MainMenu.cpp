// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"

void UMainMenu::Setup()
{
	bIsFocusable = true;
	AddToViewport();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(TakeWidget());

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	FInputModeGameOnly InputMode;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;

	RemoveFromParent();
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(BackToMenuButton != nullptr)) return false;
	BackToMenuButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::ReturnToMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		FString Address = IPAddressField->GetText().ToString();
		//if (Address != null)
		//{
			MenuInterface->Join(Address);
		//}
	}
}

void UMainMenu::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	this->MenuInterface = NewMenuInterface;
}