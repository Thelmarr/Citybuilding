// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameStateBase.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

ACPP_GameStateBase::ACPP_GameStateBase() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("GameState created")));
	}
	UE_LOG(LogTemp, Warning, TEXT("GameState created in CPP"));
}

void ACPP_GameStateBase::SetClockwork(float DeltaTime) {
	//Adjust real world time to game time through TimeUnit
	Clockwork += DeltaTime * TimeUnit;
}

void ACPP_GameStateBase::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameState BeginPlay in CPP"));
}

void ACPP_GameStateBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("GameState ticking %f"), Clockwork));
	}
	SetClockwork(DeltaTime);
	UpdateTimeDate();
	UE_LOG(LogTemp, Warning, TEXT("GameState ticking in CPP"));
}

void ACPP_GameStateBase::UpdateTimeDate() {
	//Clockwork divided by specific intervals gives date and time units
	//Clockwork = whole values give hours passed in game
	
	//hours equal remainder of mod 24
	ClockHour = FMath::Fmod(Clockwork, 24);
	//minutes equal whole division of clockwork multiplied by 60
	ClockMinute = floor((Clockwork - floor(Clockwork)) * 60);


	//days equal whole division of clockwork by 24 and mod 30
	CalDay = FMath::Fmod(floor(Clockwork / 24), 30);
	//months equal whole division of clockwork by 24 * 30 and mod 12
	CalMonth = FMath::Fmod(floor(Clockwork / (24 * 30)), 12);
	//years equal whole division of clockwork by 24 * 30 * 12
	CalYear = floor(Clockwork / (24 * 30 * 12));

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("%f/%f/%f %f:%f"), CalYear, CalMonth, CalDay, ClockHour, ClockMinute));
	}
}