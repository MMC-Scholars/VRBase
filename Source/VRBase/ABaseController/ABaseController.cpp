

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

	//first, removed inputs from invalid entities
	int32 i = 0;
	while (i < m_aRegisteredEntities.Num()) {
		if (!m_aRegisteredEntities[i].m_ent)
			m_aRegisteredEntities.RemoveAt(i);
		else
			i++;
	}

	//iterate through registered entities and check if any of them should be triggered.
	for (i = 0; i < m_aRegisteredEntities.Num(); i++) {
		SEntityInputTriggerRequirement* trig = &m_aRegisteredEntities[i];
		bool buttonActivated = false;
		if (trig->m_bOnReleased && (trig->m_iButton & m_iButtonsReleased)) {
			buttonActivated = true;
		}
		else if (!trig->m_bOnReleased && (trig->m_iButton & m_iButtonsPressed)) {
			buttonActivated = true;
		}
		if (buttonActivated) {
			trig->m_ent->Use(this);
		}
	}

	//reset our trackers for button changes
	m_iButtonsPressed = m_iButtonsReleased = 0;
}

void ABaseController::RegisterEntityInput(IBaseEntity* pEnt, uint32 iButton, bool bOnReleased) {
	//construct an input requirement and add it to ourselves.
	m_aRegisteredEntities.Emplace(SEntityInputTriggerRequirement{ pEnt->GetEHandle(), iButton, bOnReleased });
}

/**
 * setWhichHand
 */
void ABaseController::SetWhichHand(EControllerHand h) {
	m_pWhichHand = h;
	if (h == EControllerHand::Left)
		g_pLeftController = this;
	else if (h == EControllerHand::Right)
		g_pRightController = this;
	else
		NLogger::Warning("Unknown controller registered with EControllerHand == %i", h);
}
