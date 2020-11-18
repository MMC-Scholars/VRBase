#include "Globals.h"
#include "AGameRules/AGameRules.h"

static CGlobalVars g_vars;
CGlobalVars*       g_pGlobals = &g_vars;

void CGlobalVars::update() {
    steady_clock::time_point newclock = steady_clock::now();
    duration<float>          time_elapsed =
        duration_cast<duration<float>>(newclock - m_tPrevious);

    curtime = time_elapsed.count();
    ;
}

void CGlobalVars::reset() {
    m_bReset = false;

    curtime     = 0.00f; // reset clock to zero
    m_tPrevious = steady_clock::now();

    TArray<IBaseEntity*> removedList;

    // recount number of entities
    IBaseEntity::s_iEntityCount = 0;
    for (int i = 0; i < g_entList.Num(); i++) {
        IBaseEntity* pEnt   = g_entList[i];
        AActor*      pActor = pEnt->GetActor();
        FString      name   = pActor->GetName();

        // ignore templates for actors and child actors
        // CAT stands for Child Actor Template,
        // without these we get extra entities that sneak into the
        // count but don't ever run BeginPlay() or Tick()
        if (name.StartsWith("Default") || name.EndsWith("CAT")) {
            removedList.Add(pEnt);
        } else {
            IBaseEntity::s_iEntityCount++;
        }
    }

    // remove defaults from list
    while (removedList.Num() > 0) {
        IBaseEntity* ent = removedList.Pop();
        ent->RemoveSelfFromLists();
    }

    worldcreated = true;
}

void CGlobalVars::checkReset() {
    if (m_bReset) { reset(); }
}

void CGlobalVars::markReset() {
    m_bReset     = true;
    ineditor     = true;
    worldcreated = false;

    // clear all lists and resetting entity counts
    IBaseEntity::s_iReadyEntityCount = IBaseEntity::s_iEntityCount = 0;

    for (int i = 0; i < MAX_ENTITY_COUNT; i++) {
        g_ppEntityList[i] = nullptr;
    }

    while (g_entList.Num() > 0) {
        g_entList.Pop();
    }
}