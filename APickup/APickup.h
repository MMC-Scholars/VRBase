#pragma once

#include "Components/StaticMeshComponent.h"
//#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "System/NLogger.h"
//#include "VRBase/ABaseEntity/ABaseEntity.h"

#include "APickup.generated.h"

UCLASS()
class VRBASE_API APickup : public ABaseEntity {
    GENERATED_BODY()

public:
    APickup();

    TArray<AActor*>           m_aParentActors;
    UStaticMeshComponent*     m_pPickupMeshComponent;
    UProceduralMeshComponent* m_pProcMeshComponent;

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

            if (PropertyName == FName(STRINGIZE(m_pStaticMesh)))
                m_pMat = m_pStaticMesh->GetMaterial(0);

            m_pPickupMeshComponent->SetMaterial(0, m_pMat);

            m_pProcMeshComponent->SetVisibility(false);
        }
        // static mesh is not explicitly set
        else {
            m_pPickupMeshComponent->SetStaticMesh(NULL);

            m_pMat = nullptr;
            m_pPickupMeshComponent->SetMaterial(0, m_pMat);

            m_pProcMeshComponent->SetVisibility(true);
        }

        Super::PostEditChangeProperty(PropertyChangedEvent);
    }
#endif

    virtual void Pickup(ABaseController*);
    virtual void Drop(ABaseController*);

    UFUNCTION(BlueprintNativeEvent)
    void OnPickup(ABaseController* controller);
    UFUNCTION(BlueprintNativeEvent)
    void OnDrop(ABaseController* controller);
};
