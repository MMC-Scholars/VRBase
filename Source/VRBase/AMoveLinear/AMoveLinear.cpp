

#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("m_staticMeshComponent");
}

void AMoveLinear::PreInit() {
	//m_parentLoc = GetOwner()->GetRootComponent()->GetAttachParent()->GetOwner()->GetActorLocation();
	m_startLoc = GetActorLocation();
	m_startPlane = FPlane(m_startLoc, m_vDirection);
	m_endPlane = FPlane(m_startLoc + m_vDirection, -m_vDirection);
	ABaseMoving::PreInit();
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	/*m_startLoc = GetActorLocation();
	m_startPlane = FPlane(m_startLoc, m_vDirection);
	m_endPlane = FPlane(m_startLoc + m_vDirection, -m_vDirection);
	*/
	//Edit this or ABaseMoving, glitch with grabbing.
	if (m_startPlane.PlaneDot(pController->GetActorLocation()) >= 0
		&& m_endPlane.PlaneDot(pController->GetActorLocation()) >= 0) {
		FVector locThis = GetActorLocation();
		FVector locController = pController->GetActorLocation();

		FVector thisToController = locController - locThis;

		FVector proj = thisToController.ProjectOnTo(m_vDirection);
		FVector locAlongAxis = proj + locThis;

		SetActorLocation(locAlongAxis);

		m_lCurrentLerp = (GetActorLocation() - m_startLoc).Size() / m_vDirection.Size();
		//Msg("%f", GetLerpPosition());
	}
}

void AMoveLinear::SetLerpPosition(float _lerp) {
	Super::SetLerpPosition(_lerp);
	SetActorLocation(m_startLoc + _lerp * m_vDirection);
}

void AMoveLinear::DefaultThink() {
	Super::DefaultThink();
	
}



