#include "ABaseEntity.h"
#include "AGameRules/AGameRules.h"
#include "ABaseController/ABaseController.h"

ABaseEntity::ABaseEntity() : IBaseEntity() {
	Tags.Add(TAG_BASEENTITY);
	m_pSelfAsActor = this;
	bAllowTickBeforeBeginPlay = false;
	SetActorTickEnabled(false);

	m_flUseMaxRadius = FLT_MAX;

	// initial transform
	m_tInitialTransform = FTransform(GetActorRotation(), GetActorLocation(), GetActorScale());
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
}

bool ABaseEntity::IsUseableBy(const ABaseController* pController) const {
	return GetSquaredDistanceTo(pController) < (m_flUseMaxRadius * m_flUseMaxRadius);
}