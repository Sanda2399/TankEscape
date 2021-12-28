// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKESCAPE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Changes whether a projectile will be a Homing Projectile or not.
	void EnableHoming(int Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Visual Effects")
	class UParticleSystemComponent* ProjectileTrailComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// Set if homing projectile is needed.
	bool bHoming = false;

	// How much Damage this Projectile class does.
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	// A visual asset that gives this projectile smoke particles when it has hit something.
	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	class UParticleSystem* HitParticles;

	// A audio asset that gives this projectile a 'thud' sound when it has launched from the tank.
	UPROPERTY(EditAnywhere, Category = "Audio Effects")
	class USoundBase* LaunchSoundEffect;

	// A audio asset that gives this projectile a 'thud' sound when it has hit another object.
	UPROPERTY(EditAnywhere, Category = "Audio Effects")
	USoundBase* ImpactSoundEffect;

	UFUNCTION()
	// What the Projectile will do once it has hit another object.
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
