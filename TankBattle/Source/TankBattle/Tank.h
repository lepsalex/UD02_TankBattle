// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKBATTLE_API ATank : public APawn {
    GENERATED_BODY()

  public:
    float TakeDamage(float DamageAmount,
                     struct FDamageEvent const& DamageEvent,
                     class AController* EventInstigator,
                     AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category = "Hitpoints")
    float GetHealthPercent() const;


  private:
    // Sets default values for this pawn's properties
    ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHitPoints = 50;

    UPROPERTY(VisibleAnywhere, Category = "Hitpoints")
    int32 CurrentHitPoints = 50;
};
