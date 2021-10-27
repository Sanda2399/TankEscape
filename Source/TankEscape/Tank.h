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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	//Member Variables
	// Depending on which Power Up is active, set the others to false.
	bool FireSingleShot = true;
	bool FireHomingShot = false;
	bool FireWideShot = false;

	UPROPERTY(EditAnywhere, Category = "Tank Attributes")
	float Speed = 350.f;

	// Member Functions
	void Move(float Value);
	void SetFireSingleShot();
	void SetFireHomingShot();
	void SetFireWideShot();
};
