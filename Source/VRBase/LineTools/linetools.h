#pragma once

#include "UnrealEngine.h"
#include "System/predefs.h"

//------------------------------------------------------------------------------------
void UTIL_TraceLine(FHitResult& t, const FVector& start, FVector direction, float maxDistance = (float)INT32_MAX);

void UTIL_DrawLine(FVector start, FVector end, FColor c, float thickness, ftime life);

void UTIL_DrawSpline(FVector start, FVector end, FVector force, FColor c, float thickness, ftime life);

vec UTIL_DistanceToLine(FVector v, FVector vOrigin, FVector point);