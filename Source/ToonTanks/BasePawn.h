// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

private:

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	void RotateTurret(FVector LookAtTarget);

	UPROPERTY(EditAnywhere)
	float TurretTurnRate = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	void Fire();

public:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileDamage;

	void HandleDestruction();
};
