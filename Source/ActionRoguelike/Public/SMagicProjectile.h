#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;


UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBase
{
    GENERATED_BODY()
protected:
    UFUNCTION()
    void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
    float Damage = -20.0f;

public:
    virtual void Tick(float DeltaTime) override;
};

