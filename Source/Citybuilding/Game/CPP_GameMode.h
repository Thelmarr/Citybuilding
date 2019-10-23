// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACPP_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ACPP_GameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
