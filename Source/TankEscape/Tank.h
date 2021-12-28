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

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	// Used to indicate if the Tank is alive or not.
	bool bIsAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//Member Variables

	////////////////// Components ////////////////////////
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	////////////// Tank Movement Settings ///////////////
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 350.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 130.f;

	/////////// Player Controller for the Tank /////////////
	APlayerController* TankPlayerController;

	// Member Functions

	/////// Movement ///////
	void Move(float Value);
	void Turn(float Value);

	/////// Power Up Settings ///////
	void SetFireSingleShot();
	void SetFireHomingShot();
	void SetFireWideShot();
};
