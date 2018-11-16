// © Alexandru Lepsa 2018

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController {
	GENERATED_BODY()

private:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	void AimTowardsPlayer() const;
};
