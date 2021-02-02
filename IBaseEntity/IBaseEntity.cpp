#include "IBaseEntity.h"
#include "ABasePawn/ABasePawn.h"

IBaseEntity*         g_ppEntityList[MAX_ENTITY_COUNT] = {NULL};
TArray<IBaseEntity*> g_entList;

// static variables are required to be redeclared in source file (cpp) for the linker
// to detect it
TArray<IBaseEntity*> IBaseEntity::s_aBaseEntities;
bool                 IBaseEntity::s_bHasAlreadyInitializedBaseEntities;

// a global index which keeps track of where we last inserted an entity into the
// list
static eindex g_iEntityCounter = 0;

//-------------------------------------------------------------------------------------
// EHANDLE constructor
//-------------------------------------------------------------------------------------
EHANDLE::EHANDLE(const IBaseEntity* pEnt) : m_iEnt(0) {
    if (pEnt) m_iEnt = pEnt->EntIndex();
}

//-------------------------------------------------------------------------------------
// IBaseEntity Constructor & helpers
//-------------------------------------------------------------------------------------
IBaseEntity::IBaseEntity() {
    m_tConstructionTime = g_pGlobals->curtime;

    m_tLastTimeUsed = -FLT_MAX;
}

bool IBaseEntity::DestroyEntity() { return GetActor()->Destroy(); }

void IBaseEntity::PostInit() { RegisterInputsToControllers(); }

IBaseEntity* IBaseEntity::FromActor(AActor* pActor) {
    // Epic disabled RTTI so we use this janky and hacky method instead
    IBaseEntity* pEnt = NULL;
    if (pActor->ActorHasTag(TAG_BASEENTITY))
        pEnt = (IBaseEntity*)static_cast<ABaseEntity*>(pActor);
    else if (pActor->ActorHasTag(TAG_BASEPAWN))
        pEnt = (IBaseEntity*)static_cast<ABasePawn*>(pActor);
    return pEnt;
}

//-------------------------------------------------------------------------------------
// Think system
//-------------------------------------------------------------------------------------
void IBaseEntity::DefaultThink() {}

int IBaseEntity::s_iEntityCount      = 0;
int IBaseEntity::s_iReadyEntityCount = 0;

//-------------------------------------------------------------------------------------
// Generic "use" system
//-------------------------------------------------------------------------------------
bool IBaseEntity::Use(ABaseEntity* pActivator) {
    if (IsUseable()) OnUsed(pActivator);
    return IsUseable();
}

void IBaseEntity::RegisterInputsToControllers() {
    FEntityInputRegistrationParams* pLeft =
        GetLeftControllerInputRegistrationParams();
    FEntityInputRegistrationParams* pRight =
        GetRightControllerInputRegistrationParams();

    if (!pLeft || !pRight || !ControllersReady()) return;

    auto registerButtonSetToController =
        [&](ABaseController* pController, FEntityInputRegistrationButtons* pButtons,
            bool bOnRelease) {
            if (pButtons->m_AX)
                pController->RegisterEntityInput(this, IN_AX, bOnRelease);
            if (pButtons->m_BY)
                pController->RegisterEntityInput(this, IN_BY, bOnRelease);
            if (pButtons->m_GRIP)
                pController->RegisterEntityInput(this, IN_GRIP, bOnRelease);
            if (pButtons->m_MENU)
                pController->RegisterEntityInput(this, IN_MENU, bOnRelease);
            if (pButtons->m_TRIGGER)
                pController->RegisterEntityInput(this, IN_TRIGGER, bOnRelease);
            if (pButtons->m_STICK)
                pController->RegisterEntityInput(this, IN_STICK, bOnRelease);
        };

    auto registerToController = [&](ABaseController*                pController,
                                    FEntityInputRegistrationParams* params) {
        registerButtonSetToController(pController, &params->m_onPressed, false);
        registerButtonSetToController(pController, &params->m_onReleased, true);
    };

    registerToController(g_pLeftController, pLeft);
    registerToController(g_pRightController, pRight);
}

UStaticMesh* FindMesh(const wchar_t* path) {
    ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(path);
    return meshFinder.Object;
}

UStaticMesh* FindMesh(const char* path) {
    size_t   pathLen   = strlen(path) + 1;
    wchar_t* wcharPath = new wchar_t[pathLen];
    size_t   outputSize;
    mbstowcs_s(&outputSize, wcharPath, pathLen, path, pathLen - 1);

    return FindMesh(wcharPath);
}