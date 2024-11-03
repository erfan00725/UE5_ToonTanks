// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireTimeHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	if (IsFire())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	UE_LOG(LogTemp, Display, TEXT("Inside the Turret Die"));

	Destroy();
}

bool ATurret::IsFire()
{
	if (!Tank)
		return false;

	return GetActorLocation().Equals(Tank->GetActorLocation(), FireRange) && Tank->GetIsAlive();
}

void ATurret::CheckFireCondition()
{
	if (IsFire())
	{
		Fire();
	}
}
