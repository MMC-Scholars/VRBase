// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseMoving/ABaseMoving.h"
#include "AMoveLinear.generated.h"

/**
 * 
 */
UCLASS()
class THEGREATBALLOONRACE_API AMoveLinear : public ABaseMoving
{
	GENERATED_BODY()
	
public:
	void SetPositionFromController(ABaseController* pController) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		FVector m_vDirection;

};
