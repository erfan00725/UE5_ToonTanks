// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	bool GetIsAlive() { return bIsAlive; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 125.f;

	APlayerController* TankPlayerController;

private:
	void Move(float Value);
	void Turn(float Value);

	bool bIsAlive = true;
};
