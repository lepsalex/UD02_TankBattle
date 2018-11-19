// � Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

UCLASS()
class TANKBATTLE_API ATank : public APawn {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    UFUNCTION(BlueprintCallable)
    void SetTurretReference(UTankTurret* TurretToSet);

    void AimAt(FVector HitLocation) const;

    UFUNCTION(BlueprintCallable)
    void Fire();

  protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

  private:
    // Sets default values for this pawn's properties
    ATank();

    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 6000.f;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
