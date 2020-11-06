#include "APickup.h"
#include "ABaseController/ABaseController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "System/NLogger.h"

#define DEFAULT_SIZE 20

APickup::APickup() {
    // set default mesh
    m_pStaticMesh = NULL;

    // static mesh component
    m_pPickupMeshComponent =
        CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
    m_pPickupMeshComponent->SetStaticMesh(m_pStaticMesh);

    // set default material
    m_pMat = m_pPickupMeshComponent->GetMaterial(0);

    // set root component
    RootComponent = m_pPickupMeshComponent;

    // enable overlap
    m_pPickupMeshComponent->SetGenerateOverlapEvents(true);

    // simulate physics
    m_pPickupMeshComponent->SetSimulatePhysics(true);
}

TArray<AActor*> APickup::GetPickupParents() { return m_aParentActors; }

UStaticMeshComponent* APickup::GetPickupMeshComponent() {
    return m_pPickupMeshComponent;
}

bool APickup::SetSimulatePickupPhysics(bool physics) {
    m_pPickupMeshComponent->SetSimulatePhysics(physics);
    return physics;
}

bool APickup::SetPickupRenderCustomDepth(bool isRenderingCustomDepth) {
    m_pPickupMeshComponent->SetRenderCustomDepth(isRenderingCustomDepth);
    return isRenderingCustomDepth;
}

void APickup::Pickup(ABaseController* controller) {
    if (m_pPickupMeshComponent->GetStaticMesh()) {
        SetSimulatePickupPhysics(false);
        AttachToActor(controller, FAttachmentTransformRules::KeepWorldTransform);
        m_aParentActors.Add(controller);

        OnPickup(controller);
    } else {
        NLogger::Warning("Error: Pickup static mesh is null");
    }
}

void APickup::Drop(ABaseController* controller) {
    if (m_pPickupMeshComponent->GetStaticMesh()) {
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        // Attach to the next parent in line
        m_aParentActors.Remove(controller);

        if (m_aParentActors.Num() > 0)
            AttachToActor(m_aParentActors[0],
                          FAttachmentTransformRules::KeepWorldTransform);
        else
            m_pPickupMeshComponent->SetSimulatePhysics(true);

        OnDrop(controller);
    }
}

// allows for overriding in C++ classes
void APickup::OnPickup_Implementation(ABaseController* controller) {}
void APickup::OnDrop_Implementation(ABaseController* controller) {}
