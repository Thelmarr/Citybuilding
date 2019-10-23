// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameModeBase.h"

ACPP_GameModeBase::ACPP_GameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	UE_LOG(LogTemp, Warning, TEXT("GameMode created in CPP"));
}

void ACPP_GameModeBase::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameMode BeginPlay in CPP"));
}

void ACPP_GameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("GameMode ticking in CPP"));
}
