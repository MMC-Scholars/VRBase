#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_pAxis = CreateDefaultSubobject<USplineComponent>("spline axis");
	RootComponent = m_pAxis;
	m_pPickupMeshComponent->SetupAttachment(RootComponent);
}

void AMoveLinear::OnConstruction(const FTransform& transform) {
	Super::OnConstruction(transform);

	// set mesh initial lerp
	m_vTempAttachLoc = m_pAxis->GetLocationAtSplineInputKey(m_lInitialLerp, ESplineCoordinateSpace::World);
	SetPositionFromController(NULL);
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	// set world location
	FVector pos = m_pAxis->FindLocationClosestToWorldLocation(m_vTempAttachLoc, ESplineCoordinateSpace::World);
	m_pPickupMeshComponent->SetWorldLocation(pos);

	// set lerp from spline lerp value
	SetLerpPosition(m_pAxis->FindInputKeyClosestToWorldLocation(pos));
}