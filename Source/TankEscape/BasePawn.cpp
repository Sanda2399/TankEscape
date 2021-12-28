// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////////// Pawn Components //////////
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh -> SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);


	////////// Pawn Projectile Spawn Point Components //////////
	ProjectileSpawnPointMiddle = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Middle"));
	ProjectileSpawnPointMiddle -> SetupAttachment(TurretMesh);
	SpawnPoints.Emplace(ProjectileSpawnPointMiddle);

	ProjectileSpawnPointLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Left"));
	ProjectileSpawnPointLeft -> SetupAttachment(TurretMesh);
	SpawnPoints.Emplace(ProjectileSpawnPointLeft);

	ProjectileSpawnPointRight = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Right"));
	ProjectileSpawnPointRight -> SetupAttachment(TurretMesh);
	SpawnPoints.Emplace(ProjectileSpawnPointRight);
}

void ABasePawn::HandleDestruction()
{
	if (DeathEffect)
	{
		// Spawn the Death Smoke once this pawn has died.
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}
}

////////////// Movement //////////////
void ABasePawn::RotateTurret(FVector LookAtLocation)
{
	FVector ToTarget = LookAtLocation - TurretMesh -> GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh  -> SetWorldRotation(LookAtRotation);
}


///////////////// BasePawn Power Up (Firing) Settings /////////////////
// * Create Blueprint Widget 
//   to indicate to the player that they have changed to a new firing mode! *
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
		UE_LOG(LogTemp, Warning, TEXT("Fired Single Shot"));
		
		FVector ProjectileSpawnPointMiddleLocation = ProjectileSpawnPointMiddle -> GetComponentLocation();
		FRotator ProjectileSpawnPointMiddleRotation = ProjectileSpawnPointMiddle -> GetComponentRotation();

		// Spawns a Projectile and makes sure homing missiles are off.
		AProjectile* Projectile = GetWorld() -> SpawnActor<AProjectile>(ProjectileType, ProjectileSpawnPointMiddleLocation, ProjectileSpawnPointMiddleRotation);

		// Sets the owner of the spawned projectile to the instance of the Object that spawned it.
		Projectile -> SetOwner(this);
	}
	else if (bFireHomingShot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired Homing Shot"));

		FVector ProjectileSpawnPointMiddleLocation = ProjectileSpawnPointMiddle -> GetComponentLocation();
		FRotator ProjectileSpawnPointMiddleRotation = ProjectileSpawnPointMiddle -> GetComponentRotation();

		// Spawns a Projectile and makes sure homing missiles are on.
		AProjectile* Projectile = GetWorld() -> SpawnActor<AProjectile>(ProjectileType, ProjectileSpawnPointMiddleLocation, ProjectileSpawnPointMiddleRotation);

		// Sets the owner of the spawned projectile to the instance of the Object that spawned it.
		Projectile -> SetOwner(this);
	}
	else if (bFireWideShot) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired Wide Shot"));

		// Creation of a Projectiles array in order to be able to set their owners.
		TArray <AProjectile*> Projectiles;

		// Spawns a projectile for each spawn point available.
		for (int i = 0; i < SpawnPoints.Num(); i++)
		{
			FVector ProjectileSpawnPointLocation = SpawnPoints[i] -> GetComponentLocation();
			FRotator ProjectileSpawnPointRotation = SpawnPoints[i] -> GetComponentRotation();

			// Spawns a Projectile and makes sure homing missiles are off.
			Projectiles.Emplace(GetWorld() -> SpawnActor<AProjectile>(ProjectileType, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation));
		}

		// Sets the owner for each spawned projectile.
		for (AProjectile* Projectile : Projectiles)
		{
			Projectile -> SetOwner(this);
		}
	}
}