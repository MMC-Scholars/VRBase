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

    // TODO deprecate
    /*
    // execute all the pointer-based thinks
    for (eindex i = 0; i < numBaseEntities; i++) {
        if (IBaseEntity::s_aBaseEntities[i]->GetNextThink() > g_pGlobals->curtime) {
            IBaseEntity::s_aBaseEntities[i]->Think();
        }
    }
    */

    // update globals
    // g_pGlobals->update();
}

void AGameBase::InitializeBaseEntities() {
    eindex iNumEntities = IBaseEntity::s_aBaseEntities.Num();

    for (eindex i = 0; i < iNumEntities; i++)
        IBaseEntity::s_aBaseEntities[i]->PreInit();

    for (eindex i = 0; i < iNumEntities; i++)
        IBaseEntity::s_aBaseEntities[i]->PostInit();

    IBaseEntity::s_bHasAlreadyInitializedBaseEntities = true;
}