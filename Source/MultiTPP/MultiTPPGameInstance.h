// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MultiTPPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UMultiTPPGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

	virtual void Init() override;

public:
	UMultiTPPGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION()
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

private:
	class TSubclassOf<UUserWidget> MenuClass;
};
