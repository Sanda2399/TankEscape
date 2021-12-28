// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TANKESCAPE_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// What to do when Pawn's health reached zero.
	void HandleDestruction();

	///////////////// BasePawn Power Up (Firing) Settings /////////////////
	void SetFiringMode(int Value);

	bool bFireSingleShot = true;
	bool bFireHomingShot = false;
	bool bFireWideShot = false;

protected:
	////////////// Movement //////////////
	void RotateTurret(FVector LookAtLocation);

	///////////////// BasePawn Power Up (Firing) Settings /////////////////
	void FireProjectile();

private:
	////////////// Components //////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPointMiddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPointLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPointRight;

	// Array for Spawn Points
	TArray<USceneComponent*> SpawnPoints;

	// Use in the Blueprint to set the type of Projectile to be spawned. The type of projectile must be based on 'class AProjectile'.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Settings")
	TSubclassOf<class AProjectile> ProjectileType;

	// Visual Effect that will occur on pawn death.
	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	class UParticleSystem* DeathEffect;

	// Audio Effect that will occur on pawn death.
	UPROPERTY(EditAnywhere, Category = "Audio Effects")
	class USoundBase* DestroyedSoundEffect;

	// Camera Shake effect that will occur when a Pawn has died.
	UPROPERTY(EditAnywhere, Category = "Camera Effects")
	TSubclassOf<class UCameraShakeBase> OnDeathCameraShake;
};