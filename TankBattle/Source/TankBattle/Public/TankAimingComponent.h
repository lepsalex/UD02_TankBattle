// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
    Reloading,
    Aiming,
    Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    void AimAt(FVector HitLocation);

  protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

  private:
    UTankAimingComponent();

    void MoveBarrel(FVector AimDirection);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    double LastFireTime = 0;

};
