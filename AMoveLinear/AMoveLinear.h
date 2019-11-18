/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseMoving/ABaseMoving.h"
#include "AMoveLinear.generated.h"

UCLASS()
class VRBASE_API AMoveLinear : public ABaseMoving {
	GENERATED_BODY()

	public:
		AMoveLinear();

		void PreInit() override;
		void DefaultThink() override;
		void SetPositionFromController(ABaseController* pController) override;
		void SetLerpPosition(float _lerp) override;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		FVector										m_vDirection;
		FVector										m_vOriginalDirection;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		UStaticMeshComponent*						m_staticMesh;
	
		// FVector									m_parentLoc;
		FVector										m_parentToThis;
		FVector										m_startLoc;
		FPlane										m_startPlane;
		FPlane										m_endPlane;
		bool										m_hasParent;
};