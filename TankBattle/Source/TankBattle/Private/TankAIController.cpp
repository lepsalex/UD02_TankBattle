// © Alexandru Lepsa 2018

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto ControllerdTank = GetPawn();
    auto AimingComponent = ControllerdTank->FindComponentByClass<UTankAimingComponent>();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!ensure(ControllerdTank && PlayerTank && AimingComponent)) { return; }

    MoveToActor(PlayerTank, MoveAcceptanceRadius);
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
        AimingComponent->Fire();
    }
}
