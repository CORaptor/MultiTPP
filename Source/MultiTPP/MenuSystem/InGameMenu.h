// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UInGameMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ReturnToMainMenu();
};
