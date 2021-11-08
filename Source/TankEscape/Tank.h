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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	//Member Variables

	///////////// Tank Power Up (Firing) Settings ////////////
	bool FireSingleShot = true;
	bool FireHomingShot = false;
	bool FireWideShot = false;

	////////////// Tank Movement Settings ///////////////
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 350.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 130.f;

	// Player Controller for the Tank
	APlayerController* PlayerControllerRef;

	// Member Functions
	/////// Movement ///////
	void Move(float Value);
	void Turn(float Value);

	/////// Power Ups ///////
	void SetFireSingleShot();
	void SetFireHomingShot();
	void SetFireWideShot();
};
