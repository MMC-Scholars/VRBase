#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_pAxis = CreateDefaultSubobject<USplineComponent>("spline axis");
	RootComponent = m_pAxis;
	m_pPickupMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMoveLinear::PreInit() {
	m_vOriginalDirection = m_vDirection;
	m_hasParent = GetRootComponent()->GetAttachParent() != nullptr;

	// when attached to another actor, this is not at its start loc
	if (m_hasParent) {
		FTransform parentTransform = GetRootComponent()->GetAttachParent()->GetOwner()->GetActorTransform();
		// vector from parent to original location of this (m_startLoc stays constant)
		m_startLoc = GetActorLocation() - parentTransform.GetLocation();
		m_parentToThis = m_startLoc;
		m_startPlane = FPlane(GetActorLocation(), m_vDirection);
		m_endPlane = FPlane(GetActorLocation() + m_vDirection, -m_vDirection);		
	} else {
		m_startLoc = GetActorLocation();
		m_startPlane = FPlane(m_startLoc, m_vDirection);
		m_endPlane = FPlane(m_startLoc + m_vDirection, -m_vDirection);
	}
	Super::PreInit();
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	Msg("setting position from controlller");

	// set world location
	FVector pos = m_pAxis->FindLocationClosestToWorldLocation(m_vTempAttachLoc, ESplineCoordinateSpace::World);
	m_pPickupMeshComponent->SetWorldLocation(pos);

	float points = (float) m_pAxis->GetNumberOfSplinePoints() - 1;
	Msg("points: %f", points);
	//	SetLerpPosition();
}

void AMoveLinear::SetLerpPosition(float _lerp) {
	Super::SetLerpPosition(_lerp);
}

void AMoveLinear::DefaultThink() {
	Super::DefaultThink();	
}
