// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CPP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACPP_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ACPP_GameState();

	//virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	//Calendar day at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Day")
	int64 CalDay = 1;

	//Calendar month at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Month")
	int64 CalMonth = 1;

	//Calendar year at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Year")
	int64 CalYear = 0;
	
	//counts the number of passed days since game start for calendar calculation
	int64 DaysSinceStart = 0;

	//Day time at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Hour")
	int64 ClockHour = 0;
	//Day time at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Minutes")
	int64 ClockMinute = 0;

	//Game hours per second passed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameTime", DisplayName = "Time Unit")
	float TimeUnit = 12.5f;

	//How much time has passed (in float)
	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	float Clockwork = 0.f;
	//Level of Gamespeed
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Game Speed")
	int64 GameSpeed = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void SetClockwork(float DeltaTime, float Speed);

	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void UpdateTimeDate();

};
