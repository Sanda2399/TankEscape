// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TANKESCAPE_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();


private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	// Depending on which Power Up is active, set the others to false.
	bool FireSingleShot = true;
	bool FireHomingShot = false;
	bool FireWideShot = false;
};
