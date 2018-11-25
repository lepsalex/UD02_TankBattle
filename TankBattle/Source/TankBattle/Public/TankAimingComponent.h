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
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

    void AimAt(FVector HitLocation);

    UTankBarrel* GetBarrel();

  protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

  private:
    UTankAimingComponent();

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    void MoveBarrel(FVector AimDirection);
};
