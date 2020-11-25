#include "ABaseEntity.h"
#include "ABaseController/ABaseController.h"
#include "AGameBase/AGameBase.h"

ABaseEntity::ABaseEntity() : IBaseEntity() {
    m_pSelfAsActor            = this;
    bAllowTickBeforeBeginPlay = false;
    SetActorTickEnabled(false);

    m_flUseMaxRadius = FLT_MAX;
}

void ABaseEntity::BeginPlay() {
    g_pGlobals->checkReset();
    Super::BeginPlay();
    IBaseEntity::BeginPlay();
    ReportReady();

    // if the game has already started, call initializations
    if (g_pGameBase && g_pGameBase->GameReady()) {
        PreInit();
        PostInit();
    }

    // initial world transform (rotation, location, scale)
    m_tInitialTransform =
        FTransform(GetActorRotation(), GetActorLocation(), GetActorScale());
}

bool ABaseEntity::IsUseableBy(const ABaseController* pController) const {
    return GetSquaredDistanceTo(pController) < (m_flUseMaxRadius * m_flUseMaxRadius);
}
