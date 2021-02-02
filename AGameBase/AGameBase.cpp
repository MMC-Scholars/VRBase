#include "AGameBase.h"

AGameBase* g_pGameBase = NULL;
AGameBase::AGameBase() : ABaseEntity() {
    g_pGameBase                   = this;
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(true);
}

void AGameBase::Tick(float deltaTime) {
    Super::Tick(deltaTime);

    // by the time Tick is called, all BeginPlay()s have been safely and successfully
    // called
    // IBaseEntity::s_bAreBaseEntitiesReady = true;
    if (!IBaseEntity::s_bHasAlreadyInitializedBaseEntities) {
        InitializeBaseEntities();
    }

    int numBaseEntities = IBaseEntity::s_aBaseEntities.Num();

    for (eindex i = 0; i < numBaseEntities; i++) {
        IBaseEntity::s_aBaseEntities[i]->DefaultThink();
    }

    // execute all the pointer-based thinks
    for (eindex i = 0; i < numBaseEntities; i++) {
        if (IBaseEntity::s_aBaseEntities[i]->GetNextThink() > g_pGlobals->curtime) {
            IBaseEntity::s_aBaseEntities[i]->Think();
        }
    }

    // update globals
    g_pGlobals->update();
}

void AGameBase::BeginPlay() {
    Super::BeginPlay();

    ADebug::Assert(s_iEntityCount == g_entList.Num(),
                   "\nIBaseEntity::s_iEntityCount == g_entList.Num()");

    m_bHasRestartedRound         = false;
    m_bHasInitializedAllEntities = false;

    m_tNextRoundRestart = -FLT_MAX;
}

void AGameBase::RestartRound() {
    // we need to do this right, otherwise when we iterate through
    // the entity list, the size of the list might change
    TArray<EHANDLE> m_aDestroyedEntities;
    // this array remembers which entities we'll destroy later

    for (int i = 0; i < g_entList.Num(); i++) {
        IBaseEntity* pEnt = g_entList[i];

        // ignore entities marked with preserve
        if (!pEnt->HasFlags(FL_ROUND_PRESERVE)) {

            // remember entities which need destruction
            if (pEnt->HasFlags(FL_ROUND_DESTROY)) {
                m_aDestroyedEntities.Add(pEnt->GetEHandle());
                continue;
            }
        }
    }

    // now destroy everything marked in the list
    while (m_aDestroyedEntities.Num() > 0) {
        EHANDLE ent = m_aDestroyedEntities[0];
        ent->DestroyEntity();
        m_aDestroyedEntities.RemoveAt(0);
    }
}

void AGameBase::InitializeAllEntities() {
    // run pre inits of all entities
    for (eindex i = 0; i < g_entList.Num(); i++) {
        g_entList[i]->SetNextThink(FLT_MAX);
        // g_entList[i]->PreInit();
    }

    // run post inits of all entities
    // for (eindex i = 0; i < g_entList.Num(); i++)
    //    g_entList[i]->PostInit();

    // mark as ready
    m_bHasInitializedAllEntities = true;
}

void AGameBase::InitializeBaseEntities() {
    eindex iNumEntities = IBaseEntity::s_aBaseEntities.Num();

    for (eindex i = 0; i < iNumEntities; i++)
        IBaseEntity::s_aBaseEntities[i]->PreInit();

    for (eindex i = 0; i < iNumEntities; i++)
        IBaseEntity::s_aBaseEntities[i]->PostInit();

    IBaseEntity::s_bHasAlreadyInitializedBaseEntities = true;
}