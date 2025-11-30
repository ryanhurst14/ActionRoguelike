// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
	
	MoveComp->InitialSpeed = 6000.0f;
	
}


void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASTeleportProjectile::Explode, DetonateDelay);
	
}

void ASTeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	EffectComp->DeactivateSystem();
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASTeleportProjectile::TeleportInstigator, TeleportDelay);
}

void ASTeleportProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

