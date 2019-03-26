// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#include "IBaseEntity.h"
#include "ABaseEntity/ABaseEntity.h"
#include "ABasePawn/ABasePawn.h"
#include "CoreMinimal.h"

IBaseEntity* g_ppEntityList[MAX_ENTITY_COUNT] = { NULL };
TArray<IBaseEntity*> g_entList;

//a global index which keeps track of where we last inserted 
//an entity into the list
static eindex g_iEntityCounter = 0; 

//-------------------------------------------------------------------------------------
// EHANDLE constructor
//-------------------------------------------------------------------------------------
EHANDLE::EHANDLE(const IBaseEntity* pEnt) : m_iEnt(0) { 
	if (pEnt)
		m_iEnt = pEnt->EntIndex();
}

//-------------------------------------------------------------------------------------
// IBaseEntity Constructor & helpers
//-------------------------------------------------------------------------------------
IBaseEntity::IBaseEntity() {
	//AddEntityToLists(this);

	m_tConstructionTime = g_pGlobals->curtime;

	m_tLastTimeUsed = -FLT_MAX;

	//If we're in a cooked game, PostDuplicate isn't called so let's call it here
	//We'll also call it if all other other BeginPlay have been called.
	if (IsCookedBuild() || g_pGlobals->worldcreated)
		AddEntityToLists(this);
}

bool IBaseEntity::DestroyEntity() {
	RemoveSelfFromLists();
	return GetActor()->Destroy();
}

void IBaseEntity::RemoveSelfFromLists() {
	g_ppEntityList[EntIndex()] = NULL;
	g_entList.Remove(this);
}

void IBaseEntity::PostDuplicate(EDuplicateMode::Type mode) {
	//Msg("Calling IBaseEntity::PostDuplicate");
	if (mode != EDuplicateMode::Normal) {
		AddEntityToLists(this);
		g_pGlobals->ineditor = false;
	}
}

void IBaseEntity::AddEntityToLists(IBaseEntity* pEnt) {
	//Msg("Adding entity to lists");
	g_entList.Add(pEnt);
	s_iEntityCount++;

	//now add it to the const-index array
	//find an empty slot
	eindex slot = -1;

	//This code finds an empty slot for us, if one exists
	int checkCount = 0;
	for (; ++g_iEntityCounter < MAX_ENTITY_COUNT && g_ppEntityList[g_iEntityCounter]; checkCount++);
	if (g_iEntityCounter != MAX_ENTITY_COUNT) {
		slot = g_iEntityCounter;
	}
	else {
		g_iEntityCounter = 0;
		checkCount = MAX_ENTITY_COUNT - checkCount;
		for (; ++g_iEntityCounter < checkCount && g_ppEntityList[g_iEntityCounter];);

		if (g_iEntityCounter != checkCount) {
			slot = g_iEntityCounter;
		}
	} //

	//check if we found a valid slot
	if (slot == -1) {
		UE_LOG(LogTemp, Error, TEXT("Could not find slot for new entity!\nThis most likely means that there are too many entities!"));
	}
	else {
		//we're good to go - assign things
		g_ppEntityList[slot] = pEnt;
		pEnt->m_iEntIndex = slot;
	}
}

void IBaseEntity::PostInit() {
	NLogger::Message(GetActor()->GetName() + __FUNCTION__);
	RegisterInputsToControllers();
}

IBaseEntity* IBaseEntity::FromActor(AActor* pActor) {
	//Epic disabled RTTI so we use this janky and hacky
	//method instead
	IBaseEntity* pEnt = NULL;
	if (pActor->ActorHasTag(TAG_BASEENTITY))
		pEnt = (IBaseEntity*) static_cast<ABaseEntity*>(pActor);
	else if (pActor->ActorHasTag(TAG_BASEPAWN))
		pEnt = (IBaseEntity*) static_cast<ABasePawn*>(pActor);
	return pEnt;
}

//---------------------------------------------------------------
// Think system
//---------------------------------------------------------------
void IBaseEntity::DefaultThink() {
	if (g_pGlobals->curtime > m_tNextRespawn) {
		Respawn();
	}
	//Msg(__FUNCTION__);
}

int IBaseEntity::s_iEntityCount = 0;
int IBaseEntity::s_iReadyEntityCount = 0;

//---------------------------------------------------------------
// Respawn system
//---------------------------------------------------------------
void IBaseEntity::Respawn() {
	m_iHealth = m_iSpawnHealth;
	m_iFlags = m_iSpawnFlags;
	//m_bThinkReady = true;
}

//---------------------------------------------------------------
// Health System
//---------------------------------------------------------------
void IBaseEntity::SetHealth(int health) {
	if (IsNotDamageable())
		return;
	int deltaHealth = health - m_iHealth;

	if (!IsInvincible())
		m_iHealth = health;

	CheckDamageEvents(deltaHealth, nullptr);
}

void IBaseEntity::TraceAttack(const CTakeDamageInfo& info) {
	if (IsNotDamageable())
		return;
	
	//get damage amount
	int damage = info.GetBaseDamage();

	//subtract damage from health
	//SetHealth(m_iHealth - info.GetBaseDamage());
	if (!IsInvincible())
		m_iHealth -= damage;

	CheckDamageEvents(-damage, &info);
}

void IBaseEntity::CheckDamageEvents(int deltaHealth, const CTakeDamageInfo* info) {
	if (deltaHealth > 0) {
		OnHealed(info);
	}
	else {
		OnTakeDamage(info);
		if (IsDead()) {
			OnKilled(info);
			if (info && info->GetAttacker()) info->GetAttacker()->OnKilled_Other(*info);
		}
		else {
			OnTakeDamage_Alive(info);
		}
	}
}

//---------------------------------------------------------------
//Generic "Use" System
//---------------------------------------------------------------
bool IBaseEntity::Use(ABaseEntity* pActivator) {
	if (IsUseable()) {
		OnUsed(pActivator);
		return true;
	}
	return false;
}

void IBaseEntity::RegisterInputsToControllers() {
	FEntityInputRegistrationParams* pLeft = GetLeftControllerInputRegistrationParams();
	FEntityInputRegistrationParams* pRight = GetRightControllerInputRegistrationParams();

	if (!pLeft || !pRight || !ControllersReady())
		return;

	auto registerButtonSetToController = [&](ABaseController* pController, FEntityInputRegistrationButtons* pButtons, bool bOnRelease) {
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
	};

	auto registerToController = [&](ABaseController* pController, FEntityInputRegistrationParams* params) {
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