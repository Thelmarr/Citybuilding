// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_PlayerPawn.generated.h"

UCLASS()
class CITYBUILDING_API ACPP_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnRight(float Rate);
	void ZoomIn();
	void ZoomOut();
	void HandleZoom(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* PlayerCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	//normalized zoom value
	//this changes spring arm length (0 = minimum) and camera angle (0 = level)
	float FZoomLevel = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float FArmLengthMin = 250.0f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float FArmLengthMax = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float FAngleMin = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Zoom")
	float FAngleMax = -30.0f;
};
