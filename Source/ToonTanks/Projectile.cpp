// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectime Movement");

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>("Trail Particle");
	TrailParticle->SetupAttachment(RootComponent);

	ProjectileMovementComp->InitialSpeed = 2500.f;
	ProjectileMovementComp->MaxSpeed = 4000.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();

	if (!MyOwner) {
		Destroy();
		return;
	}


	auto OwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);

		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

		if (HitParticle)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());

		if (HitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);

		Destroy();
	}
}


