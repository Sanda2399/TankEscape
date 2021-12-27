// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEscape_PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankEscape_PlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    // If true, allows input for the controller of the currently controlled pawn. Else, disables that input.
    if (bPlayerEnabled)
    {
        GetPawn() -> EnableInput(this);
    }
    else
    {
        GetPawn() -> DisableInput(this);
    }

    // Sets the mouse cursor to be viewed or disabled depending on the passed in 'bPlayerEnabled' variable.
    bShowMouseCursor = bPlayerEnabled;
}