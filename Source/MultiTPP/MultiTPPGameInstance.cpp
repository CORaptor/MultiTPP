// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiTPPGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"
#include "PlatformTrigger.h"

const static FName SESSION_NAME = TEXT("My Session Game");

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

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UMultiTPPGameInstance::Init()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No online subsystem found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Subsystem: %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiTPPGameInstance::HostSession);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiTPPGameInstance::CreateNewSession);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiTPPGameInstance::SessionsFound);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiTPPGameInstance::JoinSession);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Session interface not found"));
		}
	}
}

void UMultiTPPGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateNewSession(SESSION_NAME, true);
		}
	}
}

void UMultiTPPGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[0]);

	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %d"), *Index.ToString()));

	//APlayerController* PlayerController = GetFirstLocalPlayerController();
	//if (!ensure(PlayerController != nullptr)) return;

	//PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UMultiTPPGameInstance::ReturnToMenu()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Returning to main menu")));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MenuLevel", ETravelType::TRAVEL_Absolute);
}

void UMultiTPPGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Refreshing server list"));
}

void UMultiTPPGameInstance::HostSession(FName SessionName, bool Success)
{
	if (Success)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr))
			return;

		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UMultiTPPGameInstance::CreateNewSession(FName SessionName, bool Success)
{
	if (Success)
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		UE_LOG(LogTemp, Warning, TEXT("Creating new session"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Something is no yes"));
	}
}

void UMultiTPPGameInstance::SessionsFound(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Session found"));

		TArray<FString> ServerNames;

		// Test to check if adding names to the list works correctly
		//ServerNames.Add("TestServerName");

		// Searching for servers
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		for (const FOnlineSessionSearchResult& Result : SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session: %s"), *Result.GetSessionIdStr());
			ServerNames.Add(Result.GetSessionIdStr());
		}

		Menu->SetServerList(ServerNames);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No session found"));
	}
}

void UMultiTPPGameInstance::JoinSession(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString ConnectInfo;
	bool Success = SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo);
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
}

