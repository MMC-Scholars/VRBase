

#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("m_staticMeshComponent");
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
	FVector locThis = GetActorLocation();
	FVector locController = pController->GetActorLocation();

	FVector thisToController = locController - locThis;

	FVector proj = thisToController.ProjectOnTo(m_vDirection);
	FVector locAlongAxis = proj + locThis;

	SetActorLocation(locAlongAxis);
}





