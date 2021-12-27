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

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame(); // Function's Implementation is in Unreal Blueprints.

	// Declares whether the current player has won or lost the game.
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame); // Function's Implementation is in Unreal Blueprints.

private:
	// Used to have a count of the total number of towers left in the world.
	int32 TargetTowers = 0;

	// Used to have a reference to the main player's pawn.
	class ATank* Tank;

	// Used to have a reference to the main player's Controller.
	class ATankEscape_PlayerController* CurrentPlayerController;

	float GameStartCountdown = 4.f;
	
	void HandleGameStart();

	// Gets the total number of enemy towers currently left in the world.
	int32 GetTargetTowerCount();
};