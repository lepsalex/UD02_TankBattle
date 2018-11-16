// © Alexandru Lepsa 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
    Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();

    // ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) const {
    if (!Barrel) { return; }

    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    // Calculate out launch velocity
    if (UGameplayStatics::SuggestProjectileVelocity(
            this,
            OutLaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
        )
    ) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        UE_LOG(LogTemp, Warning, TEXT("%s - aiming at: %s"), *GetOwner()->GetName(), *AimDirection.ToString());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("%s - aiming at: NO FIRING SOLUTION"), *GetOwner()->GetName());
    }

}
