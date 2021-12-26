// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankEscapeGameMode_Main.generated.h"

/**
 * 
 */
UCLASS()
class TANKESCAPE_API ATankEscapeGameMode_Main : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

private:
	// Used to have a reference to the main player's pawn.
	class ATank* Tank;
};
