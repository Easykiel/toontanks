// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingTower.h"
#include "Projectile.h"
#include "Tank.h"
#include "HomingProjectile.h"

// Sets default values
AHomingTower::AHomingTower()
{

}

// Called when the game starts or when spawned
void AHomingTower::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorldTimerManager().SetTimer(ATower::FireRateTimerHandle, this, &AHomingTower::CheckFireCondition, FireRate, true);
}

void AHomingTower::Fire()
{
    // DrawDebugSphere(
    //     GetWorld(), 
    //     ProjectileSpawnPoint->GetComponentLocation(),
    //     25.f,
    //     12,
    //     FColor::Red,
    //     false,
    //     3.f);

	AHomingProjectile* HomingProjectile = GetWorld()->SpawnActor<AHomingProjectile>(HomingProjectileClass, ABasePawn::ProjectileSpawnPoint->GetComponentLocation(), ABasePawn::ProjectileSpawnPoint->GetComponentRotation());
	HomingProjectile->SetOwner(this);
}

void AHomingTower::CheckFireCondition()
{
    if (ATower::Tank && ATower::InFireRange() && ATower::Tank->bAlive)
    {
        // If in range, Fire
        Fire();
    }   
}