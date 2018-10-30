
#include "APickup.h"
#include "System/NLogger.h"
#include "ABaseController/ABaseController.h"

#define STATIC_CUBE L"StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"

APickup::APickup() {
	// set default mesh
	staticMesh = FindMesh(STATIC_CUBE);

	// static mesh component
	m_pPickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	m_pPickupMeshComponent->SetStaticMesh(staticMesh);

	// set default material
	material0 = m_pPickupMeshComponent->GetMaterial(0);
	
	// set root component
	RootComponent = m_pPickupMeshComponent;

	// enable overlap
	m_pPickupMeshComponent->bGenerateOverlapEvents = true;

	// simulate physics
	m_pPickupMeshComponent->SetSimulatePhysics(true);
}

void APickup::Pickup(ABaseController* controller) {
	m_pPickupMeshComponent->SetSimulatePhysics(false);
	AttachToActor(controller, FAttachmentTransformRules::KeepWorldTransform);
	
	OnPickup(controller);
}

void APickup::Drop(ABaseController* controller) {
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	m_pPickupMeshComponent->SetSimulatePhysics(true);
	
	OnDrop(controller);
}
