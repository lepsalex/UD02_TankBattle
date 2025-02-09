// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

  private:
    // Called from pathfinding logic by AI Controller
    void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveForward(float Throw);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendTurnRight(float Throw);

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
};
