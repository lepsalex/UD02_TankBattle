// © Alexandru Lepsa 2018

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto ControllerdTank = GetControlledTank();

    if (!ControllerdTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController begin play with controlled tank: %s"), *ControllerdTank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const {
    if (!GetControlledTank()) { return; }

    FVector HitLocation; // Out Param

    // Get world location of linetrace through crosshair
    if (GetSightRayHitLocation(HitLocation)) {
        GetControlledTank()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

    // Find the crosshair position on-screen
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation = FVector2D(AimX * ViewportSizeX, AimY * ViewportSizeY);

    // Deproject the screen position to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        // Line-trace along that direction and see what we hit
        GetLookVectorHitLocation(LookDirection, HitLocation);
        return true;
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
    FHitResult Hit;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(
                Hit,
                StartLocation,
                EndLocation,
                ECollisionChannel::ECC_Visibility)) {
        HitLocation = Hit.Location;
        return true;
    }

    // Return false and zero hit if we are not hitting anything ECC_Visibility
    HitLocation = FVector(0.F);
    return false;
}
