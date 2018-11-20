// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

  private:
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float TrackMaxDrivingForce = 40 * 1000000.f; // max-force per track (400k newtons)
};
