

#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("m_staticMeshComponent");
}

void AMoveLinear::PreInit() {
	m_vOriginalDirection = m_vDirection;
	m_hasParent = GetRootComponent()->GetAttachParent();
	// Whenever this is attached to another actor, this is not at its start loc
	if (m_hasParent) {
		Msg("HAS PARENT");
		FTransform parentTransform = GetRootComponent()->GetAttachParent()->GetOwner()->GetActorTransform();
		// Vector from parent to original location of this. m_startLoc stays constant
		m_startLoc = GetActorLocation() - parentTransform.GetLocation();
		m_parentToThis = m_startLoc;
		m_startPlane = FPlane(GetActorLocation(), m_vDirection);
		m_endPlane = FPlane(GetActorLocation() + m_vDirection, -m_vDirection);
		
	}
	else {
		Msg("NO PARENT");
		m_startLoc = GetActorLocation();
		m_startPlane = FPlane(m_startLoc, m_vDirection);
		m_endPlane = FPlane(m_startLoc + m_vDirection, -m_vDirection);
	}
	Super::PreInit();
}
// Work on AMoveLinear, find out recalculating startPlane and endPlane
void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	if (m_hasParent) {
		Msg("HAS PARENT: SET POSITION");
		FTransform parentTransform = GetRootComponent()->GetAttachParent()->GetOwner()->GetActorTransform();
		m_vDirection = parentTransform.Rotator().RotateVector(m_vOriginalDirection);
		m_parentToThis = parentTransform.Rotator().RotateVector(m_startLoc);
		m_startPlane = FPlane(parentTransform.GetLocation() + m_parentToThis, m_vDirection);
		m_endPlane = FPlane(parentTransform.GetLocation() + m_parentToThis + m_vDirection, -m_vDirection);
	}

	if (m_startPlane.PlaneDot(pController->GetActorLocation()) >= 0
		&& m_endPlane.PlaneDot(pController->GetActorLocation()) >= 0) {
		FVector locThis = GetActorLocation();
		FVector locController = pController->GetActorLocation();

		FVector thisToController = locController - locThis;

		FVector proj = thisToController.ProjectOnTo(m_vDirection);
		FVector locAlongAxis = proj + locThis;

		SetActorLocation(locAlongAxis);

		//m_lCurrentLerp = (GetActorLocation() - m_startLoc).Size() / m_vDirection.Size();
		//Msg("%f", GetLerpPosition());
	}
}	/*m_startLoc = GetActorLocation();
	m_startPlane = FPlane(m_startLoc, m_vDirection);
	m_endPlane = FPlane(m_startLoc + m_vDirection, -m_vDirection);
	*/

void AMoveLinear::SetLerpPosition(float _lerp) {
	Super::SetLerpPosition(_lerp);
	SetActorLocation(m_startLoc + _lerp * m_vDirection);
}

void AMoveLinear::DefaultThink() {
	Super::DefaultThink();	
}



