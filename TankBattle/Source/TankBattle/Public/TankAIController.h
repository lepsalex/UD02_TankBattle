// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController {
    GENERATED_BODY()

  private:
    virtual void BeginPlay() override;

    void Tick(float DeltaTime) override;

    UTankAimingComponent* AimingComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    float MoveAcceptanceRadius = 30;
};
