// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#include "IBaseEntity.h"
#include "CBaseEntity/CBaseEntity.h"
#include "CBasePawn/CBasePawn.h"
#include "CoreMinimal.h"

IBaseEntity* g_ppEntityList[MAX_ENTITY_COUNT] = { NULL };
static TArray<IBaseEntity*> g_EntityListSmall;
TArray<IBaseEntity*>* g_ppEntityListSmall = &g_EntityListSmall;


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
	AddEntityToLists(this);

	m_tConstructionTime = g_pGlobals->curtime;
}

bool IBaseEntity::DestroyEntity() {
	return GetActor()->Destroy();
}

void IBaseEntity::AddEntityToLists(IBaseEntity* pEnt) {
	g_ppEntityListSmall->Add(pEnt);

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

IBaseEntity* IBaseEntity::FromActor(AActor* pActor) {
	//Epic disabled RTTI so we use this janky and hacky
	//method instead
	IBaseEntity* pEnt = NULL;
	if (pActor->ActorHasTag(TAG_BASEENTITY))
		pEnt = (IBaseEntity*) static_cast<CBaseEntity*>(pActor);
	else if (pActor->ActorHasTag(TAG_BASEPAWN))
		pEnt = (IBaseEntity*) static_cast<CBasePawn*>(pActor);
	return pEnt;
}

//---------------------------------------------------------------
// Think system
//---------------------------------------------------------------
void IBaseEntity::DefaultThink() {
	if (g_pGlobals->curtime > m_tNextRespawn) {
		Respawn();
	}
}

//---------------------------------------------------------------
// Respawn system
//---------------------------------------------------------------
void IBaseEntity::Respawn() {
	m_iHealth = m_iSpawnHealth;
	m_iFlags = m_iSpawnFlags;
	m_bThinkReady = true;
}

//---------------------------------------------------------------
// Health System
//---------------------------------------------------------------
void IBaseEntity::SetHealth(int health) {
	int deltaHealth = m_iHealth - health;
	m_iHealth = health;
	CheckDeath(deltaHealth, nullptr);
}

void IBaseEntity::TraceAttack(const CTakeDamageInfo& info) {
	//get damage amount
	int damage = info.GetBaseDamage();

	//subtract damage from health
	SetHealth(m_iHealth - info.GetBaseDamage());

	CheckDeath(info.GetBaseDamage(), &info);
}

void IBaseEntity::CheckDeath(int deltaHealth, const CTakeDamageInfo* info) {
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

