// © Alexandru Lepsa 2018

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation) const {
    if (TankAimingComponent) {
        TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    }
}

void ATank::Fire() {
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if (TankAimingComponent && isReloaded) {
        UTankBarrel* Barrel = TankAimingComponent->GetBarrel();
        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
                                      ProjectileBlueprint,
                                      Barrel->GetSocketLocation(FName("Projectile")),
                                      Barrel->GetSocketRotation(FName("Projectile"))
                                  );

        Projectile->LaunchProjectile(LaunchSpeed);

        LastFireTime = FPlatformTime::Seconds();
    }
}

void ATank::SetAimingComponent(UTankAimingComponent* TankAimingComponentToSet) {
    TankAimingComponent = TankAimingComponentToSet;
}
