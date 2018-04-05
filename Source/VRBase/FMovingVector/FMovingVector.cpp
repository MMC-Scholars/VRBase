#include "FMovingVector.h"
#include "System\\Globals.h"

FMovingVector::FVector(const FVector& v) : FVector(v), vel(0,0,0) {}

void FMovingVector::UpdateAll() {
	float dt = g_pGlobals->frametime;
	for (int i = 0; i < s_pVectors.Num(); i++) {
		FMovingVector& v = *(s_pVectors[i]);
		v.X += v.vel.X * dt;
		v.Y += v.vel.Y * dt;
		v.Z += v.vel.Z * dt;
	}
}
