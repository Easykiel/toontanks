// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

// Called when the game starts or when spawned
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    TargetTowers = GetTargetTowerCount();

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);

        FTimerHandle PlayerEnabledTimerHandle;
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true); 

        GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, TimerDelegate, StartDelay, false);
    }
    
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
        }

        GameOver(false);
        
    } else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}