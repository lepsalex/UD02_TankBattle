// © Alexandru Lepsa 2018

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControllerdTank = GetControlledTank();

	if (!ControllerdTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possessing a tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController begin play with controlled tank: %s"), *ControllerdTank->GetName());
	}

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not finding PlayerTank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController begin play with found player tank: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!GetControlledTank() || !GetPlayerTank()) { return; }
	AimTowardsPlayer();
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer() const {
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
