// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControllerdTank = GetControlledTank();

	if (!ControllerdTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possessing a tabk"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController begin play with controlled tank: %s"), *ControllerdTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}