// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent {
    GENERATED_BODY()

  public:
    // -1 is max downward and 1 is max upward
    void Elevate(float RelativeSpeed);

  private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 8.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationDegrees = 40.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationDegrees = 0.f;

};
