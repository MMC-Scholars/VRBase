

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseMoving/ABaseMoving.h"
#include "AMoveLinear.generated.h"

/**
 * 
 */
UCLASS()
class VRBASE_API AMoveLinear : public ABaseMoving
{
	GENERATED_BODY()

	
public:
	AMoveLinear();

	void PreInit() override;

	void SetPositionFromController(ABaseController* pController) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		FVector m_vDirection;
	FVector m_vOriginalDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		UStaticMeshComponent* m_staticMesh;

	void SetLerpPosition(float _lerp) override;

	void DefaultThink() override;

	//FVector m_parentLoc;
	FVector m_startLoc;
	FPlane m_startPlane;
	FPlane m_endPlane;
	bool m_hasParent;
};