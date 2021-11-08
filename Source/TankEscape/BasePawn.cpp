// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh -> SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMesh);
}

////////////// Movement //////////////
void ABasePawn::RotateTurret(FVector LookAtLocation)
{
	FVector ToTarget = LookAtLocation - TurretMesh -> GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh  -> SetWorldRotation(LookAtRotation);
}


///////////////// BasePawn Power Up (Firing) Settings /////////////////
void ABasePawn::SetFiringMode(int Value)
{
	switch (Value)
	{
	// Single Shot
	case 1:
		bFireSingleShot = true;
		bFireHomingShot = false;
		bFireWideShot = false;
		break;

	// Homing Shot
	case 2:
		bFireSingleShot = false;
		bFireHomingShot = true;
		bFireWideShot = false;
		break;
		
	// Wide Shot
	case 3:
		bFireSingleShot = false;
		bFireHomingShot = false;
		bFireWideShot = true;
		break;
	
	default:
		bFireSingleShot = false;
		bFireHomingShot = false;
		bFireWideShot = false;
		break;
	}
}

void ABasePawn::FireProjectile()
{
	if (bFireSingleShot)
	{
		FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint -> GetComponentLocation();
		DrawDebugSphere(
			GetWorld(),
			ProjectileSpawnPointLocation,
			25.f,
			12,
			FColor::Red,
			false,
			3.f
		);
	}
	else if (bFireHomingShot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired Homing Shot"));
	}
	else if (bFireWideShot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired Wide Shot"));
	}
}