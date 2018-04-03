#include "Globals.h"
#include "CoreMinimal.h"
#include "AGameRules/AGameRules.h"

static CGlobalVars g_vars;
CGlobalVars* g_pGlobals = &g_vars;

void CGlobalVars::update() {
	clock_t newclock = clock();
	frametime = 1.0f * (newclock - m_tPrevious) / CLOCKS_PER_SEC;
	m_tPrevious = newclock;

	curtime = curtime + frametime;
}

void CGlobalVars::reset() {
	m_bReset = false;
	Msg("CGlobalVars::reset\n");
	
	curtime = -99999.99f; //lowest value with 2 decimal digits, appoximmately

	TArray<IBaseEntity*> removedList;

	//recount number of entities
	IBaseEntity::s_iEntityCount = 0;
	for (int i = 0; i < g_entList.Num(); i++) {
		IBaseEntity* pEnt = g_entList[i];
		AActor* pActor = pEnt->GetActor();
		FString name = pActor->GetName();
		if (name.StartsWith("Default")) {
			removedList.Add(pEnt);
		}
		else {
			IBaseEntity::s_iEntityCount++;
		}
	}

	//now remove defaults from list
	while (removedList.Num() > 0) {
		IBaseEntity* ent = removedList.Pop();
		ent->RemoveSelfFromLists();
	}
}

void CGlobalVars::checkReset() {
	Msg(__FUNCTION__);
	if (m_bReset)
		reset();
}

void CGlobalVars::markReset() {
	m_bReset = true;
	ineditor = true;

	//clear all lists
	IBaseEntity::s_iReadyEntityCount = IBaseEntity::s_iEntityCount = 0;
	for (int i = 0; i < MAX_ENTITY_COUNT; i++) {
		g_ppEntityList[i] = nullptr;
	}
	while (g_entList.Num() > 0)
		g_entList.Pop();
}