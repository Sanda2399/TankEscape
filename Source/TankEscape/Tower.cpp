// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Turret Rotation
    if (PlayerTank)
    {
        TankCurDistance = FVector::Dist(GetActorLocation(), PlayerTank -> GetActorLocation());

        if (TankCurDistance <= FiringRange)
        {
            RotateTurret(PlayerTank -> GetActorLocation());
        }
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

