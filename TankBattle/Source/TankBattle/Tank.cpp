// © Alexandru Lepsa 2018

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const {
    return (float)CurrentHitPoints / (float)StartingHitPoints;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHitPoints);

    CurrentHitPoints -= DamageToApply;

    return DamageToApply;
}
