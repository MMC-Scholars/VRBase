
//#include "APickup.h"
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

// procedural mesh placeholder
#if WITH_EDITOR
    m_pProcMeshComponent =
        CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
    // create procedural mesh
    // Depth, Height, Width
    FVector cornerBBL =
        FVector(DEFAULT_SIZE / -2, DEFAULT_SIZE / -2, DEFAULT_SIZE / -2);
    FVector cornerBBR =
        FVector(DEFAULT_SIZE / 2, DEFAULT_SIZE / -2, DEFAULT_SIZE / -2);
    FVector cornerBTL =
        FVector(DEFAULT_SIZE / -2, DEFAULT_SIZE / -2, DEFAULT_SIZE / 2);
    FVector cornerBTR =
        FVector(DEFAULT_SIZE / 2, DEFAULT_SIZE / -2, DEFAULT_SIZE / 2);
    FVector cornerFBL =
        FVector(DEFAULT_SIZE / -2, DEFAULT_SIZE / 2, DEFAULT_SIZE / -2);
    FVector cornerFBR =
        FVector(DEFAULT_SIZE / 2, DEFAULT_SIZE / 2, DEFAULT_SIZE / -2);
    FVector cornerFTL =
        FVector(DEFAULT_SIZE / -2, DEFAULT_SIZE / 2, DEFAULT_SIZE / 2);
    FVector cornerFTR =
        FVector(DEFAULT_SIZE / 2, DEFAULT_SIZE / 2, DEFAULT_SIZE / 2);

    TArray<FVector> Vertices;
    Vertices.Add(cornerBBL); // 0
    Vertices.Add(cornerBBR); // 1
    Vertices.Add(cornerBTL); // 2
    Vertices.Add(cornerBTR); // 3
    Vertices.Add(cornerFBL); // 4
    Vertices.Add(cornerFBR); // 5
    Vertices.Add(cornerFTL); // 6
    Vertices.Add(cornerFTR); // 7

    // declare vertices ccw to face outwards
    TArray<int32> Triangles;
    // back
    Triangles.Add(1);
    Triangles.Add(0);
    Triangles.Add(3);

    Triangles.Add(0);
    Triangles.Add(2);
    Triangles.Add(3);

    // left
    Triangles.Add(0);
    Triangles.Add(4);
    Triangles.Add(6);

    Triangles.Add(0);
    Triangles.Add(6);
    Triangles.Add(2);

    // right
    Triangles.Add(1);
    Triangles.Add(3);
    Triangles.Add(5);

    Triangles.Add(3);
    Triangles.Add(7);
    Triangles.Add(5);

    // bottom
    Triangles.Add(0);
    Triangles.Add(1);
    Triangles.Add(5);

    Triangles.Add(0);
    Triangles.Add(5);
    Triangles.Add(4);

    // top
    Triangles.Add(3);
    Triangles.Add(2);
    Triangles.Add(6);

    Triangles.Add(3);
    Triangles.Add(6);
    Triangles.Add(7);

    // front
    Triangles.Add(4);
    Triangles.Add(5);
    Triangles.Add(6);

    Triangles.Add(5);
    Triangles.Add(7);
    Triangles.Add(6);

    // generate mesh
    m_pProcMeshComponent->CreateMeshSection_LinearColor(
        0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(),
        TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);

    // attach procedural mesh
    m_pProcMeshComponent->SetupAttachment(RootComponent);
#endif

    // enable overlap
    m_pPickupMeshComponent->SetGenerateOverlapEvents(true);

    // simulate physics
    m_pPickupMeshComponent->SetSimulatePhysics(true);
}

TArray<AActor*> APickup::Get_Parent_Actors2() {
	return m_aParentActors;
}

void APickup::Pickup(ABaseController* controller) {
    if (m_pPickupMeshComponent->GetStaticMesh()) {
        m_pPickupMeshComponent->SetSimulatePhysics(false);
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