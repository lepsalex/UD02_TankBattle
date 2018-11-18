// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

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

  private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    void MoveBarrel(FVector AimDirection);
};
