// © Alexandru Lepsa 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

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

    FTankDelegate OnTankDeath;


  private:
    // Sets default values for this pawn's properties
    ATank();

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Setup")
    int32 StartingHitPoints = 50;

    UPROPERTY(VisibleAnywhere, Category = "Hitpoints")
    int32 CurrentHitPoints;
};
