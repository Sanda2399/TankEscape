// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEscapeGameMode_Main.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ATankEscapeGameMode_Main::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank -> HandleDestruction();

        // Get the Tank's player controller and disable movement and mouse input.
        if (Tank -> GetTankPlayerController())
        {
            Tank -> DisableInput(Tank -> GetTankPlayerController());
            Tank -> GetTankPlayerController() -> bShowMouseCursor = false;
        }
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower -> HandleDestruction();
    }
}

void ATankEscapeGameMode_Main::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}