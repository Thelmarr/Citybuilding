// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "CPP_PlayerPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "CPP_PlayerPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"

ACPP_PlayerController::ACPP_PlayerController() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	if (GetPawn()) {
		PlayerPawn = Cast<ACPP_PlayerPawn>(GetPawn());
	}
}

void ACPP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("MousePan", IE_Pressed, this, &ACPP_PlayerController::OnDragPressed);
	InputComponent->BindAction("MousePan", IE_Released, this, &ACPP_PlayerController::OnDragReleased);

}

void ACPP_PlayerController::OnDragPressed() {
	BKeyDown = true;
	this->GetMousePosition(MouseXStart, MouseYStart);
	//get old rotation
	if (!PlayerPawn) {
		PlayerPawn= Cast<ACPP_PlayerPawn>(GetPawn());
	}
	PawnRotation_old = PlayerPawn->GetRootComponent()->GetComponentRotation();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, TEXT("Button pressed!"));
	}
}

void ACPP_PlayerController::OnDragReleased() {
	BKeyDown = false;
	MouseXStart = 0;
	MouseYStart = 0;
	PawnRotation_old = { 0,0,0 };
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, TEXT("Button released!"));
	}
}

void ACPP_PlayerController::ProcessPlayerInput(float DeltaTime, bool bGamePaused) {
	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (BKeyDown) {
		OnDragUpdate(DeltaTime);
	}
}

void ACPP_PlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ProcessPlayerInput(DeltaTime, bGamePaused);
}

void ACPP_PlayerController::OnDragUpdate(float DeltaTime) {
	this->GetMousePosition(MouseX, MouseY);
	
	//rotates Actor correctly
	PlayerPawn->GetRootComponent()->SetWorldRotation(FRotator(PawnRotation_old.Pitch, FMath::FInterpTo(PawnRotation_old.Yaw, PawnRotation_old.Yaw - (MouseX - MouseXStart), DeltaTime, 10.f), PawnRotation_old.Roll), false, false, ETeleportType::None);
}