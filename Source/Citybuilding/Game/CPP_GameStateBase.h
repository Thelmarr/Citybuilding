// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CPP_GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACPP_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
private:


protected:


public:
	ACPP_GameStateBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	//track game time and date
	UPROPERTY(BlueprintReadOnly, Category= "GameTime")
	int64 CalYear = 0;
	UPROPERTY(BlueprintReadOnly, Category = "GameTime")
	int64 CalMonth = 1;
	UPROPERTY(BlueprintReadOnly, Category = "GameTime")
	int64 CalDay = 1;

	UPROPERTY(BlueprintReadOnly, Category = "GameTime")
	int64 ClockHour = 0;
	UPROPERTY(BlueprintReadOnly, Category = "GameTime")
	int64 ClockMinute = 0;

	//Rate of game time in hours per second IRL
	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	float TimeUnit = 1.0f;

	//How much time has passed (in float)
	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	float Clockwork = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "GameTime")
	int64 GameSpeed = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void SetClockwork(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "GameTime")
	void UpdateTimeDate();
};
