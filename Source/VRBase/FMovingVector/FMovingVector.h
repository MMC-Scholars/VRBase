#pragma once

#include "UnrealEngine.h"

class FMovingVector : public FVector {
public:
	FMovingVector(const FVector& v);
	FMovingVector(const FVector& v, const FVector& vel);
	FMovingVector(float x, float y, float z);
	FMovingVector(float x, float y, float z, float dx, float dy, float dz);
	~FMovingVector();


	FVector vel;
	inline float speed() const { return vel.Size(); }

	static void UpdateAll();

private:
	inline void addSelf() {
		s_pVectors.Add(this);
	}
	static TArray<FMovingVector*> s_pVectors;
};