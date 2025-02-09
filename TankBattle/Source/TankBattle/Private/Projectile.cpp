// © Alexandru Lepsa 2018

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "TimerManager.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Setup Mesh and Particle System
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->SetupAttachment(RootComponent);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->SetupAttachment(RootComponent);
    ImpactBlast->bAutoActivate = false;

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->SetupAttachment(RootComponent);

    // Setup movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement"));
    ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
    Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
    ImpactBlast->Activate();
    LaunchBlast->Deactivate();
    ExplosionForce->FireImpulse();

    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();

    UGameplayStatics::ApplyRadialDamage(
        this,
        ProjectileDamage,
        GetActorLocation(),
        ExplosionForce->Radius, // same radius as explosion
        UDamageType::StaticClass(),
        TArray<AActor*>() // damage all actors
    );

    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::LaunchProjectile(float Speed) {
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}

void AProjectile::OnTimerExpire() {
    Destroy();
}
