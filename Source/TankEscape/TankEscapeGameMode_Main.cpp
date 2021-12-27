// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEscapeGameMode_Main.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TankEscape_PlayerController.h"
#include "TimerManager.h"

void ATankEscapeGameMode_Main::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank -> HandleDestruction();

        // Get the CurrentPlayerController and set the input and mouse cursor viewing to off.
        if (CurrentPlayerController)
        {
            CurrentPlayerController -> SetPlayerEnabledState(false);
        }

        // Declares that the current player has lost the game.
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower -> HandleDestruction();

        // Reduce the number of towers in the world by one.
        --TargetTowers;

        if (TargetTowers == 0)
        {
            // Declares that the current player has won the game.
            GameOver(true);
        }
    }
}

void ATankEscapeGameMode_Main::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}


void ATankEscapeGameMode_Main::HandleGameStart()
{
    // Set the number of enemy towers currently in the level.
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    CurrentPlayerController = Cast<ATankEscape_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    // Will show a widget on screen with text and a countdown timer, letting the player know that the game is getting ready to start.
    StartGame();

    // Creates a coundown timer at the beginning of the game that disables input, then enables input once the timer is finished.
    if (CurrentPlayerController)
    {
        CurrentPlayerController -> SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        // Creation of a timer delegate. Used in place of a regular function address so that we can use a callback function with inputs.
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            CurrentPlayerController, 
            &ATankEscape_PlayerController::SetPlayerEnabledState, 
            true
        );

        GetWorldTimerManager()
        .SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            GameStartCountdown, 
            false
        );
    }
}

int32 ATankEscapeGameMode_Main::GetTargetTowerCount()
{
    TArray<AActor*> Towers;

    // Get the tower objects in this world and return them all in the Towers array.
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}