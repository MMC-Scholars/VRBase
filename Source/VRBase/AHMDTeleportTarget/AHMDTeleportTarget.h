// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "AHMDTeleportTarget.generated.h"

/**
 * 
 */
UCLASS()
class VRBASE_API AHMDTeleportTarget : public ABaseEntity
{
	GENERATED_BODY()

	DECLARE_CLASS_SIMPLE(AHMDTeleportTarget, ABaseEntity)

public:
	// Static list of teleport targets - initialized with a priority 1 static initializer
	// So if you want to iterate through this, it in another priority 2 static initializer
	// or in IBaseEntity::PostInit() or after.
	static TArray<AHMDTeleportTarget*> s_aTeleportTargets;
	
	// Returns target closest to given point, or NULL if no target exists
	static AHMDTeleportTarget* TargetClosestToLocation(FVector);

	// Performs a spline cast in the given direction, and returns the AHMDTeleportTarget closest
	// to the hit location, or NULL if no target exists.
	// Also renders a spline curve in the world and a circle at hit location.
	// Use this for teleporting via ABaseController.
	static AHMDTeleportTarget* SplineFind(const FVector& direction);

	//---------------------------------------------------------------------------------
	// Member functions only control the rendering of this object.
	//		The player only teleports to the highlighted teleport target.
	//---------------------------------------------------------------------------------
	void SetHighlighted(bool);
};