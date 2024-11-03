// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 500.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;

	void HandleDestruction();

private:
	class ATank* Tank;

	bool IsFire();

	void CheckFireCondition();

	FTimerHandle FireTimeHandle;
};
