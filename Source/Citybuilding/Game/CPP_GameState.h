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


	/*
	***********Calendar units***********
	*/
	
	//Calendar day at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Day")
	int CalDay = 1;

	//Calendar month at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Month")
	int CalMonth = 1;

	//Calendar year at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Year")
	int CalYear = 0;
	





	//counts the number of passed days since game start for calendar calculation
	int DaysSinceStart = 0;




	/*
	***********Clock units***********
	*/

	//Day time at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Hour")
	int ClockHour = 0;
	//Day time at game start
	UPROPERTY(EditAnywhere, Category = "GameTime", DisplayName = "Starting Minutes")
	int ClockMinute = 0;

	//Game hours per second passed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameTime", DisplayName = "Time Unit")
	float TimeUnit = 1.0f;

	//How much time has passed (in float)
	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	float Clockwork = 0.f;

	//Current Level of Gamespeed (internal)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime", DisplayName = "Game Speed")
	int CurrentGameSpeedValue = 1;


	/*
***********Game Speed Values***********
	*/

	UPROPERTY(BlueprintReadWrite, Category = "GameSpeed")
	bool bIsPaused = false;

	//Saved value for pausing game
	UPROPERTY(EditAnywhere, Category = "GameSpeed")
	int GameSpeedSaved = 0;

	TArray<int> GameSpeed = {
		0,
		1,
		6,
		24,
		120,
		336
	};

	/*
***********Calendar functions***********
	*/


	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void SetClockwork(float DeltaTime, float Speed);

	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void UpdateTimeDate();

	UFUNCTION(BlueprintPure, Category = "GameTime")
	FVector2D GetTime();

	UFUNCTION(BlueprintPure, Category = "GameTime")
	FVector GetDate();

	/*
***********GameSpeed functions***********
	*/

	UFUNCTION(BluePrintCallable, Category = "GameTime")
	void SwitchPause();

	UFUNCTION(BluePrintCallable, Category = "GameTime")
	void SetGameSpeed(int NewLevel);
	
	UFUNCTION(BluePrintPure, Category = "GameTime")
	int GetGameSpeed() const;
	
};
