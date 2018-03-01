#include "CGameRules.h"


CGameRules* g_pGamerules;
CGameRules::CGameRules() {
	g_pGameRules = this;
	g_pGlobals->reset();
}

void CGameRules::BeginPlay() {
	m_tNextRoundRestart = FLT_MIN;
}

void CGameRules::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	g_pGlobals->markReset();
}