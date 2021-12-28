// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankEscapeGameMode_Main.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initializes the current health to the value of the MaxHealth that was set.
	Health = MaxHealth;

	// Gets the owner of this Health Component and adds a callback function to be used when this component takes damage.
	GetOwner() -> OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	// Stores a reference to the current game mode.
	GameModeReference = Cast<ATankEscapeGameMode_Main>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}

	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), Health);

	if (Health <= 0.f && GameModeReference)
	{
		GameModeReference -> ActorDied(DamagedActor);
	}
}