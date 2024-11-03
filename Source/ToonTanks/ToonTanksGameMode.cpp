// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		GameOver(false);

		if (PlayerController)
			PlayerController->SetPlayerEnableState(false);
	}
	else if(ATurret* Turret = Cast<ATurret>(DeadActor))
	{
		Turret->HandleDestruction();
		if (--TargetTurrets <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	TargetTurrets = GetTargetTurretsCount();

	StartGame();

	if (PlayerController) 
	{
		PlayerController->SetPlayerEnableState(false);

		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);

		FTimerHandle PlayerEnableTimerHandle;
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int AToonTanksGameMode::GetTargetTurretsCount()
{
	TArray<AActor*> Turrets;

	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);

	return Turrets.Num();
}


