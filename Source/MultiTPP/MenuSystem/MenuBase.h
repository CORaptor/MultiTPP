// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();

	UFUNCTION()
	void Teardown();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	
	void SetMenuInterface(IMenuInterface* NewMenuInterface);

	IMenuInterface* GetMenuInterface() const;

private:
	IMenuInterface* MenuInterface;
};
