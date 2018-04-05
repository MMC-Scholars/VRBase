// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "ABaseMoving.generated.h"

/****************************************************************************
 * This class is an interface for anything that moves on 0.0-1.0 scale.
 *		Ex. Sliding door, pivoting door.
 *	Does not explicitly have to move between two settings but can also model
 *		a strength of a single setting
 *		Ex. Velocitu-scaled follower
 ***************************************************************************/
//TODO @Michael Implement all of this and add more functionality
UCLASS()
class VRBASE_API ABaseMoving : public ABaseEntity
{
public:
	GENERATED_BODY()
	
	ABaseMoving();
	
	virtual void PreInit() override;

	virtual void PostInit() override {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
	lerp m_lInitialLerp;


private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
	lerp m_lCurrentLerp;

	
	
	
	
};
