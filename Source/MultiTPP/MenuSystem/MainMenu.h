// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* NewMenuInterface);

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackToMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* IPAddressField;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void ReturnToMenu();

	UFUNCTION()
	void JoinServer();

	IMenuInterface* MenuInterface;
};
