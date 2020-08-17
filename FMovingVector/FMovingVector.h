/**
 * This software is under partial ownership by The Ohio State University,
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "System/predefs.h"
#include "UnrealEngine.h"

/**
 *-------------------------------------------------------------------------------------
 * AMovingVector
 * A general purpose moving vector. Notes on memory usage:
 * Create new ones with the "new" keyword - this is only safe to do
 * Velocities can be  modified at any time (starting in AActor::BeginPlay() and
 *from any tick or think function) These are all destroyed in
 *AGameRules::EndPlay(), but it is also safe to delete them during Tick or Think
 *functions
 *-------------------------------------------------------------------------------------
 */
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
    inline void addSelf() { s_pVectors.Add(this); }
    static bool s_bDeletingAll;
    static TArray<FMovingVector*> s_pVectors;
};

class IMovingVectorManager {
    static void UpdateAll();
    static void RemoveAndDeleteAll();
    static void Reset();
};