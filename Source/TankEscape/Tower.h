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

protected:
	virtual void BeginPlay() override;

private:
	// Member Variables
	class ATank* PlayerTank;
	float TankCurDistance;

	UPROPERTY(EditAnywhere, Category = "Tower Settings")
	float FiringRange = 450.f;
};
