// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerPawn.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include <Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

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
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshObject(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	
	
	StaticMesh->SetStaticMesh(MeshObject.Object);
	StaticMesh->SetupAttachment(SceneRoot);

	SpringArm->SetupAttachment(StaticMesh);
	//SpringArm->TargetArmLength = 500.0f;
	PlayerCamera->SetupAttachment(SpringArm);

	//setup Camera position and spring arm length
	SpringArm->TargetArmLength = FArmLevel * FArmLengthMax + (1.0f - FArmLevel)*FArmLengthMin;
	SceneRoot->SetWorldRotation({ 0.f,0.f,0.f }, false, false, ETeleportType::None);
	SpringArm->AddWorldRotation({ FAngleMax,0.f,0.f }, false, false, ETeleportType::None);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACPP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PlayerPawn::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount);
}

void ACPP_PlayerPawn::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void ACPP_PlayerPawn::TurnRight(float Rate)
{
	AddControllerYawInput(Rate);

}

void ACPP_PlayerPawn::ZoomIn()
{
	HandleZoom(0.05);
}

void ACPP_PlayerPawn::ZoomOut()
{
	HandleZoom(-0.05);
}

void ACPP_PlayerPawn::HandleZoom(float Amount) {
	//Clamp to normalized values
	FZoomLevel += Amount;
	FZoomLevel = FMath::Clamp<float>(FZoomLevel, 0.0f, 1.0f);

	//Adjust Arm Length
	SpringArm->TargetArmLength = FZoomLevel * FArmLengthMax + (1 - FZoomLevel) * FArmLengthMin;

	//Adjust Angle
	float FAngleLerp = FZoomLevel * FAngleMax + (1 - FZoomLevel) * FAngleMin;
	FAngleLerp = FMath::Clamp<float>(FAngleLerp, FAngleMax, FAngleMin);
	SpringArm->SetWorldRotation({ FAngleLerp, 0.f, 0.f }, false, false, ETeleportType::None);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Zoom Level: %f"), FZoomLevel));
	}
}

// Called every frame
void ACPP_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

