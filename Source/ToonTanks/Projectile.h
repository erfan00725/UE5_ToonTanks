// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UProjectileMovementComponent* ProjectileMovementComp;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float NewDamage);

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage = 20.f;
};
