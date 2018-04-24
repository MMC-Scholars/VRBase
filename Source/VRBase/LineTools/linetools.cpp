#include "linetools.h"
#include "System/system.h"
#include "AGameRules/AGameRules.h"
#include "Components/LineBatchComponent.h"

#define sqr(a) ((a)*(a))

void UTIL_DrawLine(FVector start, FVector end, FColor c, float thickness, ftime life) {
	//Msg("Checking drawing line!\n");
	if (!g_pGameRules || !g_pGameRules->GetWorld() || !g_pGameRules->GetWorld()->LineBatcher)
		return;
	g_pGameRules->GetWorld()->LineBatcher->DrawLine(start, end, c, SDPG_World, thickness, life);
}

#define SPLINE_STEP 5.f
void UTIL_DrawSpline(FVector start, FVector end, FVector force, 
	FColor c, float thickness, ftime life) {
	if (!g_pGameRules || !g_pGameRules->GetWorld() || !g_pGameRules->GetWorld()->LineBatcher)
		return;
	//Msg("Drawing spline");
	ULineBatchComponent* lb = g_pGameRules->GetWorld()->LineBatcher;

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