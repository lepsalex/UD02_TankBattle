// © Alexandru Lepsa 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
    // TODO - Clamp values to 1 and -1
    UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), Throttle);
}
