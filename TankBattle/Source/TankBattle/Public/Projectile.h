// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class TANKBATTLE_API AProjectile : public AActor {
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    AProjectile();

    void LaunchProjectile(float Speed);

  private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void OnTimerExpire();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    UProjectileMovementComponent* ProjectileMovement = nullptr;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere)
    URadialForceComponent* ExplosionForce = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 10;
};
