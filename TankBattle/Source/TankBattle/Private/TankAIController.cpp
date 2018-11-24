// © Alexandru Lepsa 2018

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto ControllerdTank = Cast<ATank>(GetPawn());
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!ensure(ControllerdTank && PlayerTank)) { return; }

    MoveToActor(PlayerTank, MoveAcceptanceRadius);
    ControllerdTank->AimAt(PlayerTank->GetActorLocation());
    ControllerdTank->Fire();
}
