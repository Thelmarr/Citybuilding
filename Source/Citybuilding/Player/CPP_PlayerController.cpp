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
	QOldRot = PlayerPawn->GetRootComponent()->GetComponentRotation().Quaternion();
	PawnRotation_old = PlayerPawn->GetRootComponent()->GetComponentRotation();
	CameraRotOld = PlayerPawn->getCameraComponentRef()->GetComponentRotation();
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
		OnDragUpdate();
	}
}

void ACPP_PlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ProcessPlayerInput(DeltaTime, bGamePaused);
}

void ACPP_PlayerController::OnDragUpdate() {

	//TODO: Get Player Pawn
	//TODO: Get mouse X position and update yaw
	this->GetMousePosition(MouseX, MouseY);
	
	//TODO: Make new rotation quaternion from rotation axis
	
	//PlayerPawn->SetActorRotation(FRotator(PawnRotation_old.Pitch, PawnRotation_old.Yaw + MouseX - MouseXStart, PawnRotation_old.Roll), ETeleportType::None);
	
	//rotates Actor correctly
	PlayerPawn->GetRootComponent()->SetWorldRotation(FRotator(PawnRotation_old.Pitch, PawnRotation_old.Yaw - (MouseX - MouseXStart), PawnRotation_old.Roll), false, false, ETeleportType::None);
	
	
	//PlayerPawn->getCameraComponentRef()->SetWorldRotation(FRotator(CameraRotOld.Pitch, CameraRotOld.Yaw - (MouseX - MouseXStart), CameraRotOld.Roll), false, false, ETeleportType::None);
	
	//Rotates SpringArm correctly
	PlayerPawn->getSpringArmComponentRef()->SetWorldRotation(FRotator(CameraRotOld.Pitch, CameraRotOld.Yaw - (MouseX - MouseXStart), CameraRotOld.Roll), false, false, ETeleportType::None);
	FRotator CurRotRoot = PlayerPawn->GetRootComponent()->GetComponentRotation();
	FRotator CurRotSpring = PlayerPawn->getSpringArmComponentRef()->GetComponentRotation();
	FRotator CurRotCam = PlayerPawn->getCameraComponentRef()->GetComponentRotation();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("Root Rotation:   %.2fP/%.2fY/%.2fR"), CurRotRoot.Pitch, CurRotRoot.Yaw, CurRotRoot.Roll));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("Spring Rotation: %.2fP/%.2fY/%.2fR"), CurRotSpring.Pitch, CurRotSpring.Yaw, CurRotSpring.Roll));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, FString::Printf(TEXT("Camera Rotation: %.2fP/%.2fY/%.2fR"), CurRotCam.Pitch, CurRotCam.Yaw, CurRotCam.Roll));
	}

	//PlayerPawn->getSpringArmComponentRef()->SetWorldRotation(FRotator(PawnRotation_old.Pitch, PawnRotation_old.Yaw + (MouseX - MouseXStart), PawnRotation_old.Roll), false, false, ETeleportType::None);

	//PlayerPawn->GetRootComponent()->SetWorldRotation(FRotator(PawnRotation_old.Pitch,PawnRotation_old.Yaw + MouseX - MouseXStart,PawnRotation_old.Roll),false, false, ETeleportType::None);
	
}