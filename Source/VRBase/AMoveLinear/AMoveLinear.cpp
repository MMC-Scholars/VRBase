

#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	FVector locThis = GetActorLocation();
	FVector locController = pController->GetActorLocation();

	FVector locAlongAxis;
	FVector thisToController = locController - locThis;

	FVector proj = thisToController.ProjectOnTo(m_vDirection);
	locAlongAxis = proj + locThis;

	SetActorLocation(locAlongAxis);
}


