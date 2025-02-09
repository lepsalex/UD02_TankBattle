// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

  private:
    UTankTrack();

    virtual void BeginPlay() override;

    void DriveTrack();

    void ApplySidwaysForce() const;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float TrackMaxDrivingForce = 40 * 1000000.f; // max-force per track (400k newtons)

    float CurrentThrottle = 0;
};
