// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class TANKBATTLE_API ATank : public APawn {
    GENERATED_BODY()

  public:
    void AimAt(FVector HitLocation) const;

    UFUNCTION(BlueprintCallable)
    void SetBarrelReference(UTankBarrel* BarrelToSet);

  protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

  private:
    // Sets default values for this pawn's properties
    ATank();

    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 100000.f; // todo: find sensible default

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
