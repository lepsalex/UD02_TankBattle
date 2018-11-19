// � Alexandru Lepsa 2018

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // No need to protect pointers at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation) const {
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
    if (!Barrel) { return; }

    GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
    TankAimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
    TankAimingComponent->SetTurretReference(TurretToSet);
}
