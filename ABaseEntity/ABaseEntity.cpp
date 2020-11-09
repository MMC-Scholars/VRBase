#include "ABaseEntity.h"
#include "ABaseController/ABaseController.h"
#include "AGameRules/AGameRules.h"
#include "System/NLogger.h"

ABaseEntity::ABaseEntity() : IBaseEntity() {
    m_pSelfAsActor            = this;
    bAllowTickBeforeBeginPlay = false;
    SetActorTickEnabled(false);

    m_flUseMaxRadius = FLT_MAX;
}

void ABaseEntity::BeginPlay() {
    g_pGlobals->checkReset();
    AActor::BeginPlay();
    ReportReady();

    // if the game has already started, call initializations
    if (g_pGameRules && g_pGameRules->GameReady()) {
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
