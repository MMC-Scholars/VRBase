// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "LineDrawer.generated.h"

/**
 * An entity which handles and dispatches line drawing jobs
 */
UCLASS()
class VRBASE_API ALineDrawer : public ABaseEntity
{
	GENERATED_BODY()

	void PreInit() override {}
	void DefaultThink() override;

	
	
};
