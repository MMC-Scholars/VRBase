#include "FMovingVector/FMovingVector.h"
#include "System/Globals.h"

// all FMovingVector constructors register the vector into the global list

FMovingVector::FMovingVector(const FVector& v) : FVector(v), velocity(0,0,0) {
	addSelf();
}

FMovingVector::FMovingVector(const FVector& v, const FVector& vel) : FVector(v), velocity(vel) {
	addSelf();
}

FMovingVector::FMovingVector(vec x, vec y, vec z) : FVector(x, y, z), velocity(0, 0, 0) {
	addSelf();
}

FMovingVector::FMovingVector(vec x, vec y, vec z, vec dx, vec dy, vec dz) : FVector(x, y, z), velocity(dx, dy, dz) {
	addSelf();
}

bool FMovingVector::s_bDeletingAll = false;
TArray<FMovingVector*> FMovingVector::s_pVectors;

void IMovingVectorManager::UpdateAll() {
	ftime dt = g_pGlobals->frametime;
	for (int i = 0; i < FMovingVector::s_pVectors.Num(); i++) {
		FMovingVector& v = *(FMovingVector::s_pVectors[i]);
		v.X += v.velocity.X * dt;
		v.Y += v.velocity.Y * dt;
		v.Z += v.velocity.Z * dt;
	}
}

void IMovingVectorManager::RemoveAndDeleteAll() {
	while (FMovingVector::s_pVectors.Num() > 0) {
		FMovingVector* pv = FMovingVector::s_pVectors[0];
		FMovingVector::s_pVectors.RemoveAt(0);
		delete pv;
	}
}

void IMovingVectorManager::Reset() {
	FMovingVector::s_bDeletingAll = false;
}
