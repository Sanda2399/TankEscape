// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TANKESCAPE_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	// Member Variables to be used for finding the Tank's current location.
	class ATank* PlayerTank = nullptr;
	float TankCurDistance;

	/////////// Tower Settings ///////////
	UPROPERTY(EditAnywhere, Category = "Tower Settings")
	float FiringRange = 450.f;

	// Verifies if tank is in Range to be fired at.
	bool InFiringRange();


	/////////// Timer Settings ///////////

	// * The Timer Handle is a way of accessing this exact timer. *
	FTimerHandle FireRateTimerHandle;

	// Adjust for Tower firing speeds.
	float FiringRate = 2.f;

	// Check whether Firing Conditions have been met such as, is tank in range, does tank exist, etc.
	void CheckFireCondition();
};
