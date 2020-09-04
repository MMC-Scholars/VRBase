#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"
#include "System/NLogger.h"
#include "VRBase/ABaseMoving/ABaseMoving.h"

#include "AMoveLinear.generated.h"

UCLASS()
class VRBASE_API AMoveLinear : public ABaseMoving {
    GENERATED_BODY()

public:
    AMoveLinear();
    virtual void OnConstruction(const FTransform& transform) override;

    void PreInit() override;
    void DefaultThink() override;
    void SetPositionFromController(ABaseController* pController) override;
    void SetLerpPosition(float _lerp) override;

    USplineComponent* m_pAxis;

    FVector m_vDirection;
    FVector m_vOriginalDirection;

    FVector m_parentToThis;
    FVector m_startLoc;
    FPlane  m_startPlane;
    FPlane  m_endPlane;
    bool    m_hasParent;
};
