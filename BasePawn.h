// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "trues"))
	USceneComponent* ProjectileSpawnPoint;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "trues"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "trues"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Component", BlueprintReadOnly, meta = (AllowPrivateAccess = "trues"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};