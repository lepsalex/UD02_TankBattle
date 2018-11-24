// © Alexandru Lepsa 2018

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
    Turret = TurretToSet;
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
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
        MoveBarrel(OutLaunchVelocity.GetSafeNormal());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("%f - No firing solution found!"), GetWorld()->GetTimeSeconds());
    }
}

UTankBarrel* UTankAimingComponent::GetBarrel() {
    return Barrel;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
    if (!ensure(Barrel && Turret)) { return; }

    // Get difference between barrel and aim rotation
    auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotatator;

    // Elevate Barrel
    Barrel->Elevate(DeltaRotator.Pitch);

    // Rotate Turret
    Turret->Rotate(DeltaRotator.Yaw);
}
