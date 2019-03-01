

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

	void SetPositionFromController(ABaseController* pController) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		FVector m_vDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMoveLinear")
		UStaticMeshComponent* m_staticMesh;


};
