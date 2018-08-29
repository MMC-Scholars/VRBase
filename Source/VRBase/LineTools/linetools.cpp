#include "linetools.h"
#include "System/system.h"
#include "AGameRules/AGameRules.h"
#include "Components/LineBatchComponent.h"
#include "UnrealEngine.h"

#define sqr(a) ((a)*(a))
#define SPLINE_STEP 5.f

#define CHN_WORLDSTATIC		(1 << ECC_WorldStatic)
#define CHN_WORLDDYNAMIC	(1 << ECC_WorldDynamic)
#define CHN_PAWN			(1 << ECC_Pawn)
#define CHN_VISIBILITY		(1 << ECC_Visibility)
#define CHN_CAMERA			(1 << ECC_Camera)
#define CHN_PHYSICSBODY		(1 << ECC_PhysicsBody)
#define CHN_DESTRUCTIBLE	(1 << ECC_Destructible)
#define CHN_ALL				(CHN_WORLDSTATIC | CHN_WORLDDYNAMIC | CHN_PAWN | CHN_CAMERA | CHN_PHYSICSBODY | CHN_DESTRUCTIBLE)


FCollisionObjectQueryParams g_coqpDefault = FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllObjects);

void UTIL_TraceLine(FHitResult& t, const FVector& start, FVector direction, float maxDistance) {
	if (!g_pGameRules || !g_pGameRules->GetWorld())
		return;

	t.Init();
	FVector end = start;
	end += direction.GetClampedToSize(maxDistance, maxDistance);
	g_pGameRules->GetWorld()->LineTraceSingleByObjectType(t, start, end, g_coqpDefault);
}

void UTIL_TraceSpline(FHitResult& t, const FVector& start, FVector direction, FVector force, uint16 maxIterations) {
	if (!g_pGameRules || !g_pGameRules->GetWorld())
		return;

	t.Init();
	uint16 iterations = 1;
	direction = direction.GetClampedToSize(SPLINE_STEP, SPLINE_STEP);
	FVector step = direction;
	FVector origForce = force;
	FVector next;
	FVector previous = start;
	while (iterations <= maxIterations && t.Time > 0.9999f) {
		t.Reset();
		next = start + direction + force;

		g_pGameRules->GetWorld()->LineTraceSingleByObjectType(t, previous, next, g_coqpDefault);
		previous = next;

		iterations++;
		force += origForce * iterations;
		direction += step;
	}
}

void UTIL_DrawLine(FVector start, FVector end, FColor c, float thickness, ftime life) {
	//Msg("Checking drawing line!\n");
	if (!g_pGameRules || !g_pGameRules->GetWorld() || !g_pGameRules->GetWorld()->LineBatcher)
		return;
	g_pGameRules->GetWorld()->LineBatcher->DrawLine(start, end, c, SDPG_World, thickness, life);
}

void UTIL_DrawSpline(FVector start, FVector end, FVector force, 
	FColor c, float thickness, ftime life) {
	if (!g_pGameRules || !g_pGameRules->GetWorld() || !g_pGameRules->GetWorld()->LineBatcher)
		return;

	//NLogger::Blurp("(%f, %f, %f)", end.X, end.Y, end.Z);
	//return;

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

vec UTIL_DistanceToLine(FVector vDirection, FVector vOrigin, FVector point) {
	FVector toPoint = point - vOrigin;
	FVector projection = toPoint.ProjectOnTo(vDirection);
	return (toPoint - projection).Size();
}