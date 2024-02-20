// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHomingProjectile::AHomingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent->bIsHomingProjectile = true;
	MovementComponent->HomingAccelerationMagnitude = HomingAccelerationMag + MovementComponent->InitialSpeed;
	MovementComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	if(Tank)
	{
		MovementComponent->HomingTargetComponent = Tank->GetRootComponent();
	}
}

// Called every frame
void AHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (InTankRange())
    {
        // If in range, rotate tower toward tank
        RotateProjectile(Tank->GetActorLocation());
		MovementComponent->ComputeHomingAcceleration(Tank->GetActorLocation(), DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("Homing Acceleration: %f"), MovementComponent->HomingAccelerationMagnitude);
    }
}

//Checks to see if Tank is in Range
bool AHomingProjectile::InTankRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // Check if the tank is in range
        if (Distance <= FireRange)
        {
            return true;
        }
    } 

    return false;
}