// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = Projectile;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	MovementComponent->InitialSpeed = ProjectileInitialSpeed;
	MovementComponent->MaxSpeed = ProjectileMaxSpeed;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Projectile->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UE_LOG(LogTemp, Warning, TEXT("Init Speed: %f\nMax Speed: %f"), MovementComponent->InitialSpeed, MovementComponent->MaxSpeed);

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Using Auto is NOT Recommended
	auto MyOwner = GetOwner();
	if (!MyOwner) 
	{
		Destroy();
		return;
	}

	// Using Auto is NOT Recommended
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	// Check if Other Actor is Valid
	// OtherActor is not damaging itself
	// OtherActor is not damaging the owner
	if (OtherActor && OtherActor != this && OtherActor != MyOwner && HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	Destroy();
}

//Rotates Protjectile
void AProjectile::RotateProjectile(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - Projectile->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	Projectile->SetWorldRotation(FMath::RInterpTo(Projectile->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		15.f));
	UE_LOG(LogTemp, Warning, TEXT("Rotating Proj"));
}