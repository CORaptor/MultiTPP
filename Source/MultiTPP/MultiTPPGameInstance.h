// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	UFUNCTION(Exec)
	void ReturnToMenu() override;

	void RefreshServerList() override;

private:
	class TSubclassOf<UUserWidget> MenuClass;

	class UMainMenu* Menu;

	void HostSession(FName SessionName, bool Success);

	void CreateNewSession(FName SessionName, bool Success);

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void SessionsFound(bool Success);

	void JoinSession(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
