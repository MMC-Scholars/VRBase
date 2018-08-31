// Fill out your copyright notice in the Description page of Project Settings.

#include "AHMDTeleportTarget.h"

TArray<AHMDTeleportTarget*> AHMDTeleportTarget::s_aTeleportTargets;

// Set up teleport target list
STATIC_INTIALIZE(teleport_target_array_setup, FIRST) {
	//clear the array, then add targets back in
	AHMDTeleportTarget::s_aTeleportTargets.Empty();

	for (eindex i = 0; i < g_entList.Num(); i++) {
		AHMDTeleportTarget* target = dynamic_cast<AHMDTeleportTarget*>(g_entList[i]);
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
}

//! TODO: Implement!
void AHMDTeleportTarget::SetHighlighted(bool bHighlighted) {
	if (bHighlighted) {

	}
	else {

	}
}