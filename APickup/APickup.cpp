#include "APickup.h"
#include "ABaseController/ABaseController.h"
#include "Materials/MaterialInstanceDynamic.h"

#define DEFAULT_SIZE 20

APickup::APickup() {
    // static mesh component
    m_pPickupMeshComponent =
        CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Pickup Mesh Component" ) );

    // set root component
    //RootComponent = m_pPickupMeshComponent
    m_pPickupMeshComponent->SetupAttachment(RootComponent);

    // enable overlap
    m_pPickupMeshComponent->SetGenerateOverlapEvents(true);

    // simulate physics
    m_pPickupMeshComponent->SetSimulatePhysics(true);
}

TArray<AActor*> APickup::GetPickupParents() { return m_aParentActors; }

bool APickup::SetPickupRenderCustomDepth(bool isRenderingCustomDepth) {
    m_pPickupMeshComponent->SetRenderCustomDepth(isRenderingCustomDepth);
    return isRenderingCustomDepth;
}

void APickup::Pickup(ABaseController* controller) {
    if (m_pPickupMeshComponent->GetStaticMesh()) {
        m_pPickupMeshComponent->SetSimulatePhysics(false);
        AttachToActor(controller, FAttachmentTransformRules::KeepWorldTransform);
        m_aParentActors.Add(controller);

        OnPickup(controller);
    } else {
        ADebug::LogWarning("Error: Pickup static mesh is null");
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
