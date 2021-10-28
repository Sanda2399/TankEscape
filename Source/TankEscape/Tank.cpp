// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent -> BindAction(TEXT("Enable Single Shot Shooting Style"), IE_Pressed, this, &ATank::SetFireSingleShot);
    PlayerInputComponent -> BindAction(TEXT("Enable Homing Shot Shooting Style"), IE_Pressed, this, &ATank::SetFireHomingShot);
    PlayerInputComponent -> BindAction(TEXT("Enable Wide Shot Shooting Style"), IE_Pressed, this, &ATank::SetFireWideShot);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef -> GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::SetFireSingleShot()
{
    FireSingleShot = true;
    FireHomingShot = false;
    FireWideShot = false;

    UE_LOG(LogTemp, Warning, TEXT("Single Shot On"));
}

void ATank::SetFireHomingShot()
{
    FireSingleShot = false;
    FireHomingShot = true;
    FireWideShot = false;

    UE_LOG(LogTemp, Warning, TEXT("Homing Shot On"));
}

void ATank::SetFireWideShot()
{
    FireSingleShot = false;
    FireHomingShot = false;
    FireWideShot = true;

    UE_LOG(LogTemp, Warning, TEXT("Wide Shot On"));
}

