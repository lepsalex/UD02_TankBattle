// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController {
    GENERATED_BODY()

  public:
    UFUNCTION()
    void OnTankDeath();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MoveAcceptanceRadius = 8000;

  private:
    virtual void BeginPlay() override;

    virtual void SetPawn(APawn* InPawn) override;

    void Tick(float DeltaTime) override;

    UTankAimingComponent* AimingComponent = nullptr;
};
