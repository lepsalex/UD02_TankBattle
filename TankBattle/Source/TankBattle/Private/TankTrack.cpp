// © Alexandru Lepsa 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
    auto ForceApplied = GetForwardVector() * FMath::Clamp(Throttle, 1.f, -1.f) * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
