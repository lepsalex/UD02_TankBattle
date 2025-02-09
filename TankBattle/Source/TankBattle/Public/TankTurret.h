// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTurret : public UStaticMeshComponent {
    GENERATED_BODY()

  public:
    // -1 is max counter-clockwise and 1 is clockwise
    void Rotate(float RelativeSpeed);

  private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 16.f;

};
