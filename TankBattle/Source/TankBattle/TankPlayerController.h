// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

  protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenAimingPos")
    float AimX = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenAimingPos")
    float AimY = 0.3333f;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 10 * 100000.f; // 10km

  private:
    void BeginPlay() override;

    void Tick(float DeltaTime) override;

    void AimTowardsCrosshair() const;

    UTankAimingComponent* AimingComponent = nullptr;

    bool GetSightRayHitLocation(FVector& HitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& Hit) const;
};
