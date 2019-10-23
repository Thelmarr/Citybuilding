// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_GameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
