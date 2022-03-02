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
    UStaticMeshComponent* m_pPickupMeshComponent;
    // TODO add procedural mesh component
    // for reference, view
    // https://github.com/MMC-Scholars/VRBase/tree/cb9ca2eb29bba46b89aada1b487c409b44a5f36d

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mesh",
              DisplayName = "Static Mesh")
    UStaticMesh* m_pStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mesh",
              DisplayName = "Material")
    UMaterialInterface* m_pMat;

    // UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mass")
    // float m_fMass;

#if WITH_EDITOR
    // set static mesh and material dynamically from within the editor
    virtual void
    PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

        FName PropertyName = PropertyChangedEvent.Property
                                 ? PropertyChangedEvent.Property->GetFName()
                                 : NAME_None;

        if (m_pPickupMeshComponent && m_pStaticMesh) {

            m_pPickupMeshComponent->SetStaticMesh(m_pStaticMesh);

            if (PropertyName == FName(toString(m_pStaticMesh)))
                m_pMat = m_pStaticMesh->GetMaterial(0);

            m_pPickupMeshComponent->SetMaterial(0, m_pMat);
        }
        // static mesh is not explicitly set
        else {
            m_pPickupMeshComponent->SetStaticMesh(NULL);

            m_pMat = nullptr;
            m_pPickupMeshComponent->SetMaterial(0, m_pMat);
        }

        Super::PostEditChangeProperty(PropertyChangedEvent);
    }
#endif
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
