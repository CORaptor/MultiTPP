// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListEntry.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UServerListEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerListEntry(const FObjectInitializer& ObjectInitializer);
	UServerListEntry(const FObjectInitializer& ObjectInitializer, FText ServerName);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameField;

	UFUNCTION()
	void OnButtonClicked();

	void Setup(class UMainMenu* Parent, uint32 Index);

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectServerButton;

protected:
	virtual bool Initialize() override;

private:
	uint32 ServerIndex;
	class UMainMenu* ParentMenu;
};
