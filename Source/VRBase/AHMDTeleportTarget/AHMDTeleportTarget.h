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

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
};

extern TArray<AHMDTeleportTarget*> g_aTeleportTargets;