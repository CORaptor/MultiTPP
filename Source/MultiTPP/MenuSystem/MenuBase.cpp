// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"

void UMenuBase::Setup()
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