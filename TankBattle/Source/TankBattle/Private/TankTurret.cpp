// © Alexandru Lepsa 2018

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.F, 1.F);
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
    auto Rotation = FMath::Clamp(RawNewRotation, -180.F, 180.F);
    SetRelativeRotation(FRotator(0, Rotation, 0));
}