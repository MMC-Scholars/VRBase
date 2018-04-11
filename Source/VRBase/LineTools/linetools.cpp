#include "linetools.h"
#include "Components/LineBatchComponent.h"

#define sqr(a) ((a)*(a))

void UTIL_DrawLine(FVector start, FVector end, FColor c, float thickness, ftime life) {
	if (!GEngine || !GEngine->GetWorld() || !GEngine->GetWorld()->LineBatcher)
		return;

	GEngine->GetWorld()->LineBatcher->DrawLine(start, end, c, SDPG_World, thickness, life);
	
}

#define SPLINE_STEP 5.f
void UTIL_DrawSpline(FVector start, FVector end, FVector force, 
	FColor c, float thickness, ftime life) {
	if (!GEngine || !GEngine->GetWorld() || !GEngine->GetWorld()->LineBatcher)
		return;

	ULineBatchComponent* lb = GEngine->GetWorld()->LineBatcher;

	FVector displacement = end - start;
	vec len = displacement.Size();
	vec step = 0.0f;
	FVector vectorStep = start;
	FVector previousStep = vectorStep;
	while (step < len) {
		lerp forceScale = 1.0f - 4 * sqr((step / len) - 0.5f);
		vectorStep = start + displacement * step / len;
		vectorStep += force * forceScale;
		lb->DrawLine(previousStep, vectorStep, c, SDPG_World, thickness, life);
		previousStep = vectorStep;
		step += SPLINE_STEP;
	}
}

vec UTIL_DistanceToLine(FVector v, FVector vOrigin, FVector point) {
	FVector toPoint = point - vOrigin;
	FVector projection = toPoint.ProjectOnTo(v);
	return (toPoint - projection).Size();
}