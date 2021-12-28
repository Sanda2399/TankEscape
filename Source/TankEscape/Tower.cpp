// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If Tank is in range, rotate the turret towards the tank.
    if (InFiringRange())
    {
        RotateTurret(PlayerTank -> GetActorLocation());
    }
}


void ATower::BeginPlay()
{
    Super::BeginPlay();

    // Get the Current Player's tank instance and store it.
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));


    // Sets a timer that allows me to have the towers fire projectiles consistently at a set rate.
    GetWorldTimerManager() // Returns an instance of a FTimerHandler.
    .SetTimer(
        FireRateTimerHandle,
        this, 
        &ATower::CheckFireCondition, 
        FiringRate, 
        true
    );
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


void ATower::CheckFireCondition()
{
    if (PlayerTank == nullptr) 
    {
        return;
    }

    // If tank within firing range and is currently alive, fire a projectile.
    if (InFiringRange() && PlayerTank -> bIsAlive)
    {
        // * Can randomize this later or have different towers set at different modes for variety. *
        SetFiringMode(1);
        FireProjectile();
    }
}


bool ATower::InFiringRange()
{
    if (PlayerTank)
    {
        // Find the current distance from the tower to the tank.
        TankCurDistance = FVector::Dist(GetActorLocation(), PlayerTank -> GetActorLocation());

        // If the Tank's distance is within firing range, return true.
        if (TankCurDistance <= FiringRange)
        {
            return true;
        }
    }
    // Return false if not in range.
    return false;
}