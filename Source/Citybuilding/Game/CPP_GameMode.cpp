// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameMode.h"

ACPP_GameMode::ACPP_GameMode() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACPP_GameMode::BeginPlay() {
	Super::BeginPlay();
}

void ACPP_GameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
