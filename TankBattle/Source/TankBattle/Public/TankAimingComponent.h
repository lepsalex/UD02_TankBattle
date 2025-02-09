// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
    OutOfAmmo,
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

    EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetAmmoCount();

  protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

  private:
    UTankAimingComponent();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void MoveBarrel();

    bool IsBarrelMoving();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 AmmoCount = 10;

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    FVector AimDirection;

    double LastFireTime = 0;
};
