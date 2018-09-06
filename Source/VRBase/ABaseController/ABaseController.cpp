

#include "ABaseController.h"

ABaseController::ABaseController() {

	// Scene component
	m_pHandScene = CreateDefaultSubobject<USceneComponent>("Hand Main");
	RootComponent = m_pHandScene;

	// Static mesh
	m_pHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Controller Mesh");
	m_pHandMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_pHandMeshComponent->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HandMesh(L"StaticMesh'/Game/Geometry/office_fridge2.office_fridge2'");
	m_pHandMeshComponent->SetStaticMesh(HandMesh.Object);
	//m_pHandMeshComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 90.0f));

	// Sphere collision
	m_pControllerCollision = CreateDefaultSubobject<USphereComponent>("Controller Collision");
	m_pControllerCollision->AttachToComponent(m_pHandMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_pControllerCollision->InitSphereRadius(12.0f);

	// Sphere Collision Overlap
	//m_pControllerCollision->bGenerateOverlapEvents = true;
	//m_pControllerCollision->OnComponentBeginOverlap.AddDynamic(this, &AHand::OnOverlapBegin);
	//m_pControllerCollision->OnComponentEndOverlap.AddDynamic(this, &AHand::OnOverlapEnd);

}

/*
// ------------------------------------------------------------
// EVENT BeginOverlap (m_pControllerCollision)
// ------------------------------------------------------------
void AHand::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		// Add actor to TArray
		m_aOverlapActors.Add(OtherActor);
		// If APickup, outline mesh
		APickup *pPickupActor = Cast<APickup>(OtherActor);
		if (pPickupActor) {
			pPickupActor->m_pBaseMesh->SetRenderCustomDepth(true);
		}
	}
}

// ------------------------------------------------------------
// EVENT EndOverlap (m_pControllerCollision)
// ------------------------------------------------------------
void AHand::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	// Remove actor from TArray
	m_aOverlapActors.Remove(OtherActor);
	// If APickup, remove mesh outline
	APickup *pPickupActor = Cast<APickup>(OtherActor);
	if (pPickupActor) {
		pPickupActor->m_pBaseMesh->SetRenderCustomDepth(false);
	}
}
*/

ABaseController* g_pLeftController;
ABaseController* g_pRightController;

void ABaseController::OnButtonsChanged() {
	m_iButtons |= m_iButtonsPressed;
	m_iButtons &= ~m_iButtonsReleased;

	//iterate through registered entities and check if any of them should be triggered.
	for (eindex i = 0; i < m_aRegisteredEntities.Num(); i++) {
		SEntityInputTriggerRequirement* trig = &m_aRegisteredEntities[i];
		if (trig->m_ent &&  /* button matching expression goes here*/) {

		}
	}

	//reset our trackers for button changes
	m_iButtonsPressed = m_iButtonsReleased = 0;
}

/**
 * setWhichHand
 */
void ABaseController::setWhichHand(EControllerHand h) {
	m_pWhichHand = h;
	//TODO map g_pLeftController and g_pRightController to specific controllers.
}
