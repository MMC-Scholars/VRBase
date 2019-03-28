

#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("m_staticMeshComponent");
	startLoc = GetActorLocation();
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	//FVector Base, FVector Normal
	//endLoc = startLoc + m_vDirection;
	FPlane startPlane = FPlane(startLoc, m_vDirection);
	//FPlane endPlane = FPlane(endLoc, m_vDirection);
	/** PlaneDot(...)
	* Calculates distance between plane and a point.
	*
	* @param P The other point.
	* @return >0: point is in front of the plane, <0: behind, =0: on the plane.
	*/
	if (startPlane.PlaneDot(GetActorLocation()) >= 0) {
		FVector locThis = GetActorLocation();
		FVector locController = pController->GetActorLocation();

		FVector thisToController = locController - locThis;

		FVector proj = thisToController.ProjectOnTo(m_vDirection);
		FVector locAlongAxis = proj + locThis;

		SetActorLocation(locAlongAxis);
	}
}





