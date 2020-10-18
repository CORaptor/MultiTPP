// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UObject/ConstructorHelpers.h"
#include "ServerListEntry.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UServerListEntry> ServerListEntryBPClass(TEXT("/Game/MenuSystem/WBP_ServerListEntry"));
	if (!ensure(ServerListEntryBPClass.Class != nullptr)) return;
	ServerListEntryClass = ServerListEntryBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	if (ServerList == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No server list widget detected."));
		return;
	}
	
	ServerList->ClearChildren();
	
	if (ServerListEntryClass != nullptr && ServerList != nullptr)
	{
		uint32 i = 0;
		
		for (const FString& ServerName : ServerNames)
		{
			UServerListEntry* ServerListEntry = CreateWidget<UServerListEntry>(this, ServerListEntryClass);
			ServerListEntry->ServerNameField->SetText(FText::FromString(ServerName));
			ServerListEntry->Setup(this, i);
			++i;
			
			ServerList->AddChild(ServerListEntry);
		}
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	if (!ensure(BackToMenuButton != nullptr)) return false;
	BackToMenuButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::HostServer()
{
	if (GetMenuInterface() != nullptr)
	{
		GetMenuInterface()->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	SetServerList({ "...searching for servers..." });
	GetMenuInterface()->RefreshServerList();
}

void UMainMenu::ReturnToMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && GetMenuInterface() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d."), SelectedIndex.GetValue());
		GetMenuInterface()->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set."));
	}
}

void UMainMenu::QuitGame()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!ensure(GameInstance != nullptr)) return;

	APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand(TEXT("quit"), true);
}
