// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseMoving/ABaseMoving.h"
#include "Components/SplineComponent.h"
#include "AMoveRotational.generated.h"

UCLASS()
class VRBASETESTING_API AMoveRotational : public ABaseMoving
{
	GENERATED_BODY()
	
	public:
		AMoveRotational();

		virtual void OnConstruction(const FTransform& transform) override;
		//void PreInit() override;
		void SetPositionFromController(ABaseController* pController) override;
		void SetLerpPosition(float _lerp) override;
		void DefaultThink() override;

		USplineComponent*							m_pAxis;

		FVector										m_vDirection;
		FVector										m_vInitialDirection;
		FVector										m_vRangeVector;
		FVector										m_vRotAxis;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving", DisplayName = "Rotational Radius", meta = (ClampMin = "0"))
		float										m_fRotRadius;
		//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving", DisplayName = "Rotational Range", meta = (ClampMin = "-360", ClampMax = "360"))
		float										m_fRotRange;
		bool										m_hasParent;
};
