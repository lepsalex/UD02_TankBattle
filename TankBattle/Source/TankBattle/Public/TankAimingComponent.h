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

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UTankAimingComponent();

    void AimAt(FVector HitLocation, float LaunchSpeed);

    void SetBarrelReference(UTankBarrel* BarrelToSet);

    void SetTurretReference(UTankTurret* TurretToSet);

  protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

  private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    void MoveBarrel(FVector AimDirection);
};
