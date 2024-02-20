// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "HomingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AHomingProjectile : public AProjectile
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHomingProjectile();
	virtual void Tick(float DeltaTime);

protected:
	void BeginPlay();

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HomingAccelerationMag = 50.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 500.f;
	
	bool InTankRange();
	
};
