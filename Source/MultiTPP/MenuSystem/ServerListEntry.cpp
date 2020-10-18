// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"

UServerListEntry::UServerListEntry(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	if (ServerNameField != nullptr)
	{
		ServerNameField->SetText(FText::FromString("NoName"));
	}
}

UServerListEntry::UServerListEntry(const FObjectInitializer& ObjectInitializer, FText ServerName) : Super(ObjectInitializer)
{
	if (ServerNameField != nullptr)
	{
		ServerNameField->SetText(ServerName);
	}
}

bool UServerListEntry::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	if (!ensure(SelectServerButton != nullptr)) return false;
	SelectServerButton->OnClicked.AddDynamic(this, &UServerListEntry::OnButtonClicked); 
	
	return true;
}

void UServerListEntry::OnButtonClicked()
{
	if (ParentMenu == nullptr) return;
	
	ParentMenu->SelectIndex(ServerIndex);
}

void UServerListEntry::Setup(UMainMenu* Parent, uint32 Index)
{
	if (Parent == nullptr) return;

	ServerIndex = Index;
	ParentMenu = Parent;
}

