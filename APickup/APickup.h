#pragma once

#include "ABaseEntity/ABaseEntity.h"

#include "APickup.generated.h"

UCLASS()
class VRBASE_API APickup : public ABaseEntity {
    GENERATED_BODY()

public:
    APickup();

private:
    TArray<AActor*> m_aParentActors;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* m_pPickupMeshComponent;

    // TODO add procedural mesh component
    // for reference, view
    // https://github.com/MMC-Scholars/VRBase/tree/cb9ca2eb29bba46b89aada1b487c409b44a5f36d

    UFUNCTION(BlueprintCallable)
    TArray<AActor*> GetPickupParents();

    UFUNCTION(BlueprintCallable)
    UStaticMeshComponent* GetPickupMeshComponent();

    UFUNCTION(BlueprintCallable)
    bool SetSimulatePickupPhysics(bool physics);

    UFUNCTION(BlueprintCallable)
    bool SetPickupRenderCustomDepth(bool isRenderingCustomDepth);

    virtual void Pickup(ABaseController*);
    virtual void Drop(ABaseController*);

    UFUNCTION(BlueprintNativeEvent)
    void OnPickup(ABaseController* controller);
    UFUNCTION(BlueprintNativeEvent)
    void OnDrop(ABaseController* controller);
};
