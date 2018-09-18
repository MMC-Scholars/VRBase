// Fill out your copyright notice in the Description page of Project Settings.

#include "AHMDTeleportTarget.h"
#include "LineTools/linetools.h"

TArray<AHMDTeleportTarget*> AHMDTeleportTarget::s_aTeleportTargets;

// Set up teleport target list
STATIC_INTIALIZE(teleport_target_array_setup, FIRST) {
	//clear the array, then add targets back in
	AHMDTeleportTarget::s_aTeleportTargets.Empty();

	for (eindex i = 0; i < g_entList.Num(); i++) {
		AHMDTeleportTarget* target = dynamic_cast<AHMDTeleportTarget*>(g_entList[i]->GetActor());
		if (target) {
			AHMDTeleportTarget::s_aTeleportTargets.Add(target);
		}
	}
}

AHMDTeleportTarget* AHMDTeleportTarget::TargetClosestToLocation(FVector loc) {

	ThisClass* closest = NULL;
	vec min = FLT_MAX;

	for (eindex i = 0; i < s_aTeleportTargets.Num(); i++) {
		vec dist = (s_aTeleportTargets[i]->GetActorLocation() - loc).SizeSquared();
		if (dist < min) {
			min = dist;
			closest = s_aTeleportTargets[i];
		}
	}

	return closest;
}

AHMDTeleportTarget* AHMDTeleportTarget::SplineFind(const FVector& start, const FVector& direction) {

	SLineDrawParams rendered = { FColor::Red, 6.f, (ftime) 0.1f};

	FHitResult t;
	FVector force = FVector(0, 0, -0.08f);
	UTIL_TraceSpline(t, start, direction, force, 4096, &rendered);

	FVector loc = t.Location;
	if (loc == FVector::ZeroVector)
		loc = t.TraceEnd;

	return TargetClosestToLocation(loc);
}

//! TODO: Implement!
void AHMDTeleportTarget::SetHighlighted(bool bHighlighted) {
	if (bHighlighted) {

	}
	else {

	}
}