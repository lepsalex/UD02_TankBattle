// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControllerdTank = GetControlledTank();

	if (!ControllerdTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tabk"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController begin play with controlled tank: %s"), *ControllerdTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}