// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerPawn.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include <Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h>
#include <Runtime\Engine\Classes\Engine\Engine.h>

// Sets default values
ACPP_PlayerPawn::ACPP_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot				= CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRoot);
	FloatingPawnMovement	= CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	StaticMesh				= CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SpringArm				= CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	PlayerCamera			= CreateDefaultSubobject<UCameraComponent>("PlayerCameraComponent");
	
	//bUseControllerRotationYaw = true;
	//bUseControllerRotationPitch = true;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshObject(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	
	StaticMesh->SetStaticMesh(MeshObject.Object);
	StaticMesh->SetupAttachment(SceneRoot);

	SpringArm->SetupAttachment(SceneRoot);
	//SpringArm->TargetArmLength = 500.0f;
	PlayerCamera->SetupAttachment(SpringArm);
	FloatingPawnMovement->UpdatedComponent = SceneRoot;
	//setup Camera position and spring arm length
	SpringArm->TargetArmLength = FZoomLevel * FArmLengthMax + (1.0f - FZoomLevel)*FArmLengthMin;
	//SceneRoot->SetWorldRotation({ 0.f,0.f,0.f }, false, false, ETeleportType::None);
	//SpringArm->AddWorldRotation({ FAngleMax,0.f,0.f }, false, false, ETeleportType::None);
	SpringArm->bUsePawnControlRotation = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	/*
	BUG:: When rotating the camera, the forward vector and movement component update correctly. The SpringArm rotates in the wrong direction
	
	*/
}

// Called when the game starts or when spawned
void ACPP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PlayerPawn::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetRootComponent()->GetForwardVector() * Amount);
}

void ACPP_PlayerPawn::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetRootComponent()->GetRightVector() * Amount);
}

void ACPP_PlayerPawn::TurnRight(float Value)
{

}

void ACPP_PlayerPawn::ZoomIn()
{
	FZoomLevel += 0.05;
}

void ACPP_PlayerPawn::ZoomOut()
{
	FZoomLevel -= 0.05;
}

void ACPP_PlayerPawn::HandleZoom(float DeltaTime) {
	//Clamp to normalized values
	FZoomLevel = FMath::Clamp<float>(FZoomLevel, 0.0f, 1.0f);

	//Adjust Arm Length
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, FZoomLevel * FArmLengthMax + (1 - FZoomLevel) * FArmLengthMin, DeltaTime, 10.f);


	//Adjust Angle
	float FAngleLerp = FMath::Clamp<float>(FZoomLevel * FAngleMax + (1 - FZoomLevel) * FAngleMin, FAngleMax, FAngleMin);
	FQuat NewRotationQuad = FRotator(FMath::FInterpTo(PlayerCamera->GetComponentRotation().Pitch, FAngleLerp, DeltaTime, 10.f), 0.f, 0.f).Quaternion();
	float CurrentAngle = PlayerCamera->GetComponentRotation().Pitch;
	/*
	CAMERA ROTATION BUG HERE!
	*/

	//TODO: Rotate camera aound the X axis to generate pitch difference
	//PlayerCamera->SetWorldRotation(FRotator(FMath::FInterpTo(CurrentAngle, FAngleLerp, DeltaTime, 10.f), PlayerCamera->GetComponentRotation().Yaw, PlayerCamera->GetComponentRotation().Roll), false, false, ETeleportType::None);
	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Zoom Level: %f"), FZoomLevel));
	}
}

// Called every frame
void ACPP_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleZoom(DeltaTime);

	/*
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Yellow, FString::Printf(TEXT("Root Front: %.5f/%.5f/%.5f"), GetRootComponent()->GetForwardVector().X, GetRootComponent()->GetForwardVector().Y, GetRootComponent()->GetForwardVector().Z));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, FString::Printf(TEXT("Springarm Front: %.5f/%.5f/%.5f"), SpringArm->GetForwardVector().X, SpringArm->GetForwardVector().Y, SpringArm->GetForwardVector().Z));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, FString::Printf(TEXT("Camera Front: %.5f/%.5f/%.5f"), PlayerCamera->GetForwardVector().X, PlayerCamera->GetForwardVector().Y, PlayerCamera->GetForwardVector().Z));

		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Yellow, FString::Printf(TEXT("Root Up: %.5f/%.5f/%.5f"), GetRootComponent()->GetUpVector().X, GetRootComponent()->GetUpVector().Y, GetRootComponent()->GetUpVector().Z));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, FString::Printf(TEXT("Springarm Up: %.5f/%.5f/%.5f"), SpringArm->GetUpVector().X, SpringArm->GetUpVector().Y, SpringArm->GetUpVector().Z));
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, FString::Printf(TEXT("Camera Up: %.5f/%.5f/%.5f"), PlayerCamera->GetUpVector().X, PlayerCamera->GetUpVector().Y, PlayerCamera->GetUpVector().Z));
	}
	*/
}

// Called to bind functionality to input
void ACPP_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPP_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPP_PlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ACPP_PlayerPawn::TurnRight);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACPP_PlayerPawn::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACPP_PlayerPawn::ZoomOut);
}

USpringArmComponent* ACPP_PlayerPawn::getSpringArmComponentRef() const{
	if (SpringArm) {
		return SpringArm;
	}
	else {
		return nullptr;
	}
}

UCameraComponent* ACPP_PlayerPawn::getCameraComponentRef() const {
	if (PlayerCamera) {
		return PlayerCamera;
	}
	else {
		return nullptr;
	}
}