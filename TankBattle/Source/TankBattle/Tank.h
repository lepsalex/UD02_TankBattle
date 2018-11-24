// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn {
    GENERATED_BODY()

  public:
    void AimAt(FVector HitLocation) const;

    UFUNCTION(BlueprintCallable)
    void Fire();

  protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

  private:
    // Sets default values for this pawn's properties
    ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    double LastFireTime = 0;
};
