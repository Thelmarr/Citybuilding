// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameState.h"

#include <Runtime/Engine/Classes/Engine/Engine.h>

ACPP_GameState::ACPP_GameState() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("GameState created")));
	}
	UE_LOG(LogTemp, Warning, TEXT("GameState created in CPP"));
}

void ACPP_GameState::SetClockwork(float DeltaTime, float Speed) {
	//Adjust real world time to game time through TimeUnit
	Clockwork += DeltaTime * Speed;
}

void ACPP_GameState::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameState BeginPlay in CPP"));
}

void ACPP_GameState::UpdateTimeDate() {
	//Clockwork = whole values give hours passed in game

	//hours equal remainder of mod 24
	ClockHour = FMath::Fmod(Clockwork, 24);
	//minutes equal whole division of clockwork multiplied by 60
	ClockMinute = floor((Clockwork - floor(Clockwork)) * 60);

	//update internal day count
	//a day passes every 24 hours
	DaysSinceStart = floor(Clockwork / 24);

	int64 YearsSinceStart = 0;
	int64 YearFraction = 0;
	//calculate number of regular years that have passed
	YearsSinceStart = floor(DaysSinceStart / 365);
	//calculate remaining days and correct for leap years
	//YearsFraction is defined from 0 to 364 (365 in leap years)
	YearFraction = DaysSinceStart % 365 + floor(YearsSinceStart / 4);
	//check if correction enters new year
	if (YearFraction >= 365 && YearsSinceStart % 4 == 0) {
		YearsSinceStart++;
		YearFraction = YearFraction % 365;
	}
	else if (YearFraction >= 365 && YearsSinceStart % 4 != 0) {
		YearsSinceStart++;
		YearFraction = YearFraction % 364;
	}
	CalYear = YearsSinceStart;

	//day correction for leap years
	int DayCor = 0;
	if (YearsSinceStart % 4 == 0) { DayCor = 1; }
	else { DayCor = 0; }

	//set month and Day
	//January: 0 to 30 (31 days)
	if (YearFraction < 31) {
		CalMonth = 1;
		CalDay = YearFraction + 1;
	}
	//February: 31 to 58 (28 days)
	else if (YearFraction < 59 + DayCor) {
		CalMonth = 2;
		CalDay = YearFraction - 31 + 1;
	}
	//March: 59 to 89 (31 days)
	else if (YearFraction < 90 + DayCor) {
		CalMonth = 3;
		CalDay = YearFraction - 59 - DayCor + 1;
	}
	//April: 90 to 119 (30 days)
	else if (YearFraction < 120 + DayCor) {
		CalMonth = 4;
		CalDay = YearFraction - 90 - DayCor + 1;
	}
	//May: 120 to 150 (31 days)
	else if (YearFraction < 151 + DayCor) {
		CalMonth = 5;
		CalDay = YearFraction - 120 - DayCor + 1;
	}
	//June: 151 to 180 (30 days)
	else if (YearFraction < 181 + DayCor) {
		CalMonth = 6;
		CalDay = YearFraction - 151 - DayCor + 1;
	}
	//July: 181 to 211 (31 days)
	else if (YearFraction < 212 + DayCor) {
		CalMonth = 7;
		CalDay = YearFraction - 181 - DayCor + 1;
	}
	//August: 212 to 242 (31 Days)
	else if (YearFraction < 243 + DayCor) {
		CalMonth = 8;
		CalDay = YearFraction - 212 - DayCor + 1;
	}
	//September: 243 to 272 (30 Days)
	else if (YearFraction < 273 + DayCor) {
		CalMonth = 9;
		CalDay = YearFraction - 243 - DayCor + 1;
	}
	//October: 273 to 303 (31 Days)
	else if (YearFraction < 304 + DayCor) {
		CalMonth = 10;
		CalDay = YearFraction - 273 - DayCor + 1;
	}
	//November: 304 to 333 (30 Days)
	else if (YearFraction < 334 + DayCor) {
		CalMonth = 11;
		CalDay = YearFraction - 304 - DayCor + 1;
	}
	//December: 334 to 364 (31 Days)
	else if (YearFraction < 365 + DayCor) {
		CalMonth = 12;
		CalDay = YearFraction - 334 - DayCor + 1;
	}

	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("%02d/%02d/%04d %02d:%02d"), CalDay, CalMonth, CalYear, ClockHour, ClockMinute));
	}
}