// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectHash.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileTrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileTrailComponent"));
	ProjectileTrailComponent -> SetupAttachment(RootComponent);

	////////// Projectile Default Settings //////////
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent -> MaxSpeed = 1300.f;
	ProjectileMovementComponent -> InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Registers the function 'OnHit' to the OnComponentHit Delegate, so that whether a Hit Event occurs, 'OnHit' is called.
	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSoundEffect)
	{
		// Plays the launch sound effect whenever a projectile is shot from a Pawn.
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSoundEffect, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::EnableHoming(int Value)
{
	switch (Value)
	{
		// OFF
		case 0:
			bHoming = false;
			ProjectileMovementComponent -> bIsHomingProjectile = false;
			break;

		// ON
		case 1:
			bHoming = true;
			ProjectileMovementComponent -> bIsHomingProjectile = true;
			break;
		
		default:
			ProjectileMovementComponent -> bIsHomingProjectile = false;
			break;
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* CurOwner = GetOwner();
	if (CurOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* CurOwnerInstigator = CurOwner -> GetInstigatorController();
	UClass* ClassOfDamageType = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != CurOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, CurOwnerInstigator, this, ClassOfDamageType);

		if (HitParticles)
		{
			// Spawn Smoke visual effect.
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (ImpactSoundEffect)
		{
			// Plays the Impact sound effect whenever a projectile hits something.
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSoundEffect, GetActorLocation());
		}
		if (OnHitCameraShake)
		{
			// Creates a camera shake effect for the player when hitting something with a projectile.
			GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(OnHitCameraShake);
		}
	}

	Destroy();
}