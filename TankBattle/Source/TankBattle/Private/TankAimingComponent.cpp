// © Alexandru Lepsa 2018

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();

    // Force initial reload
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
    Turret = TurretToSet;
    Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (AmmoCount == 0) {
        FiringState = EFiringState::OutOfAmmo;
        return;
    } else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
        FiringState = EFiringState::Reloading;
        return;
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
        return;
    } else {
        FiringState = EFiringState::Locked;
        return;
    }
}

EFiringState UTankAimingComponent::GetFiringState() const {
    return FiringState;
}

int32 UTankAimingComponent::GetAmmoCount() {
    return AmmoCount;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
    if (!ensure(Barrel && Turret)) { return; }

    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    // Calculate out launch velocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                this,
                                OutLaunchVelocity,
                                StartLocation,
                                HitLocation,
                                LaunchSpeed,
                                false,
                                0,
                                0,
                                ESuggestProjVelocityTraceOption::DoNotTrace
                            );

    if (bHaveAimSolution) {
        // Move the barrel
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel();
    }
}

void UTankAimingComponent::Fire() {
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }

    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
                                      ProjectileBlueprint,
                                      Barrel->GetSocketLocation(FName("Projectile")),
                                      Barrel->GetSocketRotation(FName("Projectile"))
                                  );

        Projectile->LaunchProjectile(LaunchSpeed);

        LastFireTime = FPlatformTime::Seconds();
        AmmoCount--;
    }
}

void UTankAimingComponent::MoveBarrel() {
    if (!ensure(Barrel)) { return; }
    if (!ensure(Turret)) { return; }

    // Get difference between barrel and aim rotation
    auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotatator;

    // Elevate Barrel
    Barrel->Elevate(DeltaRotator.Pitch);

    // Rotate Turret
    if (FMath::Abs(DeltaRotator.Yaw) < 180.f) {
        Turret->Rotate(DeltaRotator.Yaw);
    } else {
        Turret->Rotate(-DeltaRotator.Yaw);
    }

}

bool UTankAimingComponent::IsBarrelMoving() {
    if (!ensure(Barrel)) { return false; }

    auto BarrelForward = Barrel->GetForwardVector();

    return !BarrelForward.Equals(AimDirection, 0.01);
}
