
#include "APickup.h"
#include "System/NLogger.h"

#define OCULUS_TOUCH_CONTROLLER_MODEL_RIGHT_PATH L"StaticMesh'/Game/Geometry/Controllers/oculus_cv1_controller_right.oculus_cv1_controller_right'"

APickup::APickup() {
	// set default mesh
	m_pMesh = FindMesh(OCULUS_TOUCH_CONTROLLER_MODEL_RIGHT_PATH);
	
	// static mesh component
	m_pPickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	m_pPickupMeshComponent->SetStaticMesh(m_pMesh);
	RootComponent = m_pPickupMeshComponent;

	// overlap
	m_pPickupMeshComponent->bGenerateOverlapEvents = true;

	// simulate physics
	m_pPickupMeshComponent->SetSimulatePhysics(true);
}

void APickup::PreInit() {
	// set static mesh to user-specified mesh
	m_pPickupMeshComponent->SetStaticMesh(m_pMesh);

}
