// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATower::ATower()
{

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (InFireRange())
    {
        // If in range, rotate tower toward tank
        RotateTurret(Tank->GetActorLocation());
    }
}

// Handles Tower Destruction when it dies
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if (Tank && InFireRange() && Tank->bAlive)
    {
        // If in range, Fire
        UE_LOG(LogTemp, Warning, TEXT("Regular In Range"));
        Fire();
    }   
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // UE_LOG(LogTemp, Warning, TEXT("Distance = %f"), Distance);

        // Check if the tank is in range
        if (Distance <= FireRange)
        {
            return true;
        }
    } 

    return false;
}