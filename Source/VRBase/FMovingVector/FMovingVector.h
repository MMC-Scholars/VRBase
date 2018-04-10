#pragma once

#include "UnrealEngine.h"
#include "System/predefs.h"

//---------------------------------------------------------------------------
// General purpose moving vectors. Notes on memory usage:
//		Create new ones with the "new" keyword - this is only safe to do
//			starting in AActor::BeginPlay() and from any tick or think function
//		Velocities can be  modified at any time
//		These are all destroyed in AGameRules::EndPlay(), but it is also safe
//			to delete them during Tick or Think functions
//---------------------------------------------------------------------------
class FMovingVector : public FVector {
	friend class IMovingVectorManager;
public:
	FMovingVector(const FVector& v);
	FMovingVector(const FVector& v, const FVector& vel);
	FMovingVector(vec x, vec y, vec z);
	FMovingVector(vec x, vec y, vec z, vec dx, vec dy, vec dz);
	~FMovingVector() {}


	FVector velocity;
	inline vec speed() const { return velocity.Size(); }

	

private:
	inline void addSelf() {
		s_pVectors.Add(this);
	}
	static bool						s_bDeletingAll;
	static TArray<FMovingVector*>	s_pVectors;
};

class IMovingVectorManager {
	static void UpdateAll();
	static void RemoveAndDeleteAll();
	static void Reset();
};