// © Alexandru Lepsa 2018

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet) {
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if (!Barrel) { return; }

    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    // Calculate out launch velocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
            this,
            OutLaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            ESuggestProjVelocityTraceOption::DoNotTrace
        );

    if (bHaveAimSolution) {
        // Move the barrel
        MoveBarrel(OutLaunchVelocity.GetSafeNormal());
    }
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

    // Get difference between barrel and aim rotation
    auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotatator;

    // Elevate Barrel
    Barrel->Elevate(5);

    UE_LOG(LogTemp, Warning, TEXT("%s - aiming at: %s"), *GetOwner()->GetName(), *AimDirection.ToString());
}
