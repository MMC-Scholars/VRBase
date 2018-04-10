// Fill out your copyright notice in the Description page of Project Settings.

#include "AHMDTeleportTarget.h"

TArray<AHMDTeleportTarget*> g_aTeleportTargets;

void AHMDTeleportTarget::BeginPlay() {
	Super::BeginPlay();

	g_aTeleportTargets.Add(this);
}

void AHMDTeleportTarget::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	g_aTeleportTargets.Remove(this);
}