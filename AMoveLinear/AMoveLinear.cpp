#include "AMoveLinear.h"
#include "ABaseController/ABaseController.h"

AMoveLinear::AMoveLinear() {
    m_pAxis       = CreateDefaultSubobject<USplineComponent>("spline axis");
    RootComponent = m_pAxis;
    m_pPickupMeshComponent->SetupAttachment(RootComponent);
}

void AMoveLinear::OnConstruction(const FTransform& transform) {
    Super::OnConstruction(transform);

    // set mesh initial lerp
    m_vTempAttachLoc = m_pAxis->GetLocationAtSplineInputKey(
        m_lInitialLerp, ESplineCoordinateSpace::World);
    SetPositionFromController(NULL);
}

void AMoveLinear::PreInit() {
    m_vOriginalDirection = m_vDirection;
    m_hasParent          = GetRootComponent()->GetAttachParent() != nullptr;

    // when attached to another actor, this is not at its start loc
    if (m_hasParent) {
        FTransform parentTransform =
            GetRootComponent()->GetAttachParent()->GetOwner()->GetActorTransform();
        // vector from parent to original location of this (m_startLoc stays
        // constant)
        m_startLoc     = GetActorLocation() - parentTransform.GetLocation();
        m_parentToThis = m_startLoc;
        m_startPlane   = FPlane(GetActorLocation(), m_vDirection);
        m_endPlane     = FPlane(GetActorLocation() + m_vDirection, -m_vDirection);
    } else {
        m_startLoc   = GetActorLocation();
        m_startPlane = FPlane(m_startLoc, m_vDirection);
        m_endPlane   = FPlane(m_startLoc + m_vDirection, -m_vDirection);
    }
    Super::PreInit();
}

void AMoveLinear::SetPositionFromController(ABaseController* pController) {
    // set world location
    FVector pos = m_pAxis->FindLocationClosestToWorldLocation(
        m_vTempAttachLoc, ESplineCoordinateSpace::World);
    m_pPickupMeshComponent->SetWorldLocation(pos);

    // set lerp from spline lerp value
    SetLerpPosition(m_pAxis->FindInputKeyClosestToWorldLocation(pos));
}

void AMoveLinear::SetLerpPosition(float _lerp) { Super::SetLerpPosition(_lerp); }

void AMoveLinear::DefaultThink() { Super::DefaultThink(); }
