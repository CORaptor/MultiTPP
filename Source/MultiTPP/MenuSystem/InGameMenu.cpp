// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Bind Return-to-Main-Menu Button
	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMainMenu);

	// Bind Cancel Button
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMenuBase::Teardown);

	return true;
}

void UInGameMenu::ReturnToMainMenu()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Return to Main Menu"));

	if (GetMenuInterface() == nullptr) return;
	GetMenuInterface()->ReturnToMenu();
}
