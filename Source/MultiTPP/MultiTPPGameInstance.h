// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiTPPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTITPP_API UMultiTPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

public:
	UMultiTPPGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);
};
