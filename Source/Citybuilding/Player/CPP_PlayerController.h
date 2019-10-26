// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	void OnDragPressed();
	void OnDragReleased();
	void OnDragUpdate();
	void ProcessPlayerInput(float DeltaTime, bool bGamePaused);

	virtual void Tick(float DeltaTime) override;
	ACPP_PlayerController();
private:
	bool BKeyDown = false;
	bool bGamePaused;
	class ACPP_PlayerPawn* PlayerPawn;
	float MouseX;
	float MouseXStart;
	float MouseYStart;
	float MouseY;

	FRotator PawnRotation_old;
	FQuat QOldRot;
	FRotator CameraRotOld;
};
