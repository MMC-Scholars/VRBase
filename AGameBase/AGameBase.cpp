#include "AGameBase.h"

AGameBase* g_pGameBase = NULL;
AGameBase::AGameBase() : ABaseEntity() {
    g_pGameBase                   = this;
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(true);
}

void AGameBase::Tick(float deltaTime) {
    Super::Tick(deltaTime);

    // check for round restart
    // also check for initialization of all entities (efficient place to do it)
    if (g_pGlobals->curtime > m_tNextRoundRestart) {
        // executing round restart statement
        if (!m_bHasInitializedAllEntities && AllEntitiesReady()) {
            // initializing all entities
            InitializeAllEntities();
        } else if (!AllEntitiesReady()) {
            //?! This should never happen!
            ADebug::Assert((bool)(s_iReadyEntityCount == s_iEntityCount),
                           "s_iReadyEntityCount == s_iEntityCount");
        } else {
            // restarting round
            RestartRound();
        }
        m_tNextRoundRestart = FLT_MAX;
    }

    // execute all default thinks
    for (eindex i = 0; i < g_entList.Num(); i++) {
        // executing DefaultThink for BaseEntity g_entList[i]
        g_entList[i]->DefaultThink();
    }

    // execute all the pointer-based thinks
    for (eindex i = 0; i < g_entList.Num(); i++) {
        if (g_entList[i]->GetNextThink() > g_pGlobals->curtime) {
            g_entList[i]->Think();
        }
    }

    // update globals
    g_pGlobals->update();
}

void AGameBase::BeginPlay() {
    Super::BeginPlay();
    ADebug::Assert((bool)(s_iEntityCount = g_entList.Num()),
                   "\nIBaseEntity::s_iEntityCount = g_entList.Num()");

    m_bHasRestartedRound         = false;
    m_bHasInitializedAllEntities = false;

    m_tNextRoundRestart = -FLT_MAX;
}

void AGameBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    m_bHasInitializedAllEntities = false;
    g_pGlobals->markReset();
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
        g_entList[i]->PreInit();
    }

    // run post inits of all entities
    for (eindex i = 0; i < g_entList.Num(); i++)
        g_entList[i]->PostInit();

    // mark as ready
    m_bHasInitializedAllEntities = true;
}
