// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "HomingTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AHomingTower : public ATower
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHomingTower();

protected:
	virtual void BeginPlay();

private:
	void Fire();
	void CheckFireCondition();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AHomingProjectile> HomingProjectileClass;
};
