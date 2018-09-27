

#include "ABaseController.h"
#include "System/NLogger.h"
#include "LineTools/linetools.h"
#include "ABasePawn/ABasePawn.h"

ABaseController::ABaseController() {

	bool bLeft = false;
	if (!g_pLeftController) {
		bLeft = true;
		g_pLeftController = this;
	}
	else if (!g_pRightController) {
		g_pRightController = this;
	}

	m_bPerformedPositionFixup = false;

	// Scene component
	m_pHandScene = CreateDefaultSubobject<USceneComponent>("Hand Main");
	RootComponent = m_pHandScene;

	// Static mesh
	m_pHandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Controller Mesh");
	m_pHandMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_pHandMeshComponent->SetMobility(EComponentMobility::Movable);
	m_pHandMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	//m_pHandMeshComponent->SetStaticMesh(FindMesh(L"StaticMesh'/Game/Geometry/office_fridge2.office_fridge2'"));
	//m_pHandMeshComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 135.0f));

	/*vec horiz = 3.f;
	if (!bLeft) horiz = -horiz;
	m_pHandMeshComponent->AddRelativeLocation(FVector(0, horiz, 3));;*/
	

	// Sphere collision
	m_pControllerCollision = CreateDefaultSubobject<USphereComponent>("Controller Collision");
	m_pControllerCollision->AttachToComponent(m_pHandMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_pControllerCollision->InitSphereRadius(12.0f);

	// Sphere Collision Overlap
	//m_pControllerCollision->bGenerateOverlapEvents = true;
	//m_pControllerCollision->OnComponentBeginOverlap.AddDynamic(this, &AHand::OnOverlapBegin);
	//m_pControllerCollision->OnComponentEndOverlap.AddDynamic(this, &AHand::OnOverlapEnd);

	m_bButtonHeld = false;
}

void ABaseController::PostInit() {
	

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
#define IGNORED_ACTORS() { g_pBasePawn, g_pLeftController, g_pRightController, NULL }

void ABaseController::OnButtonsChanged() {
	m_iButtons |= m_iButtonsPressed;
	m_iButtons &= ~m_iButtonsReleased;


	// TEST AREA FOR BUTTON INPUT AND OTHER STUFF

	//-----------------------------------------------------------------------------------------------------------------
	if (m_bButtonHeld) {
		// we have released the button
		m_bButtonHeld = false;

		// Disable Haptics
		GetWorld()->GetFirstPlayerController()->SetHapticsByValue(300.0f, 0.0f, m_eWhichHand);

		//if (m_iButtonsReleased & IN_AX) {
			FVector start = GetActorLocation();
			FVector direction = GetActorForwardVector();

			AActor* ppIgnored[4] = IGNORED_ACTORS();

			FHitResult t;
			FVector force = FVector(0, 0, -0.08f);
			UTIL_TraceSpline(t, start, direction, force, 4096, NULL, ppIgnored);

			//loc will be where we hit
			FVector loc = t.Location;
			if (loc == FVector::ZeroVector)
				loc = t.TraceEnd;

			// My attempt to fade the camera the way the default VR Blueprints teleport
			//APlayerCameraManager* pCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
			//pCameraManager->StartCameraFade(0, 1, 0.1, FLinearColor::Black, false, true);

			//FTimerHandle UnusedHandle;
			//GetWorldTimerManager().SetTimer(UnusedHandle, this, [=](){
			m_pOwnerPawn->TeleportPlayer(loc);
			//	pCameraManager->StartCameraFade(1, 0, 0.1, FLinearColor::Black, false, true);
			//}, 0.1, false);
		//}
	}
	else {
		// we just pressed the button
		m_bButtonHeld = true;

	}
	//-----------------------------------------------------------------------------------------------------------------
	


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
	m_eWhichHand = h;
	bool fixup = !m_bPerformedPositionFixup;
	if (h == EControllerHand::Left) 
		g_pLeftController = this;
	else if (h == EControllerHand::Right)
		g_pRightController = this;
	else {
		NLogger::Warning("Unknown controller registered with EControllerHand == %i", h);
		fixup = false;
	}
		
	if (fixup) {
		m_bPerformedPositionFixup = true;
		
	}
}

void ABaseController::SetStaticMesh(UStaticMesh* pMesh) {
	m_pHandMeshComponent->SetStaticMesh(pMesh);
}

void ABaseController::OnUsed(ABaseEntity* pActivator) {
	
	// insert code from method above once this works 
	Msg(__FUNCTION__);
}

void ABaseController::DefaultThink() {
	
	if (m_bButtonHeld) {

		// Enable Haptics (* need to change frequency and amplitude later)
		GetWorld()->GetFirstPlayerController()->SetHapticsByValue(300.0f, 0.5f, m_eWhichHand);

		//if (m_iButtonsPressed & IN_AX) {
			SLineDrawParams rendered = { FColor::Red, 6.f, (ftime) 0.1f };

			FVector start = GetActorLocation(); //m_pHandMeshComponent->GetComponentLocation();
			FVector direction = GetActorForwardVector(); //m_pHandMeshComponent->GetForwardVector();

			FHitResult t;
			AActor* ppIgnored[] = IGNORED_ACTORS();
			FVector force = FVector(0, 0, -0.08f);
			UTIL_TraceSpline(t, start, direction, force, 4096, &rendered, ppIgnored);
			//UTIL_TraceLine(t, start, direction);

			FVector loc = t.Location;
			if (loc == FVector::ZeroVector)
				loc = t.TraceEnd;

			//then render a circle at loc
			//UTIL_DrawLine(start, loc, &rendered);
			UTIL_DrawCircle(loc, (vec) 30.f, &rendered);
		//}
	}
	
}
