#include "AGameRules.h"

AGameRules* g_pGameRules;
AGameRules::AGameRules() : ABaseEntity() {
	g_pGameRules = this;
	//g_pGlobals->reset();
	PrimaryActorTick.bCanEverTick = true;
}

void AGameRules::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	g_pGlobals->update();

	//Msg("AGameRules::Tick");
	//NLogger::Blurp("%f - %f", g_pGlobals->curtime, m_tNextRoundRestart);

	
	if (g_pGlobals->curtime > m_tNextRoundRestart) {
		NLogger::Message(FColor::Cyan, 3.0f, "Executing round restart statement");
		if (!m_bHasInitializedAllEntities && AllEntitiesReady()) {
			NLogger::Message(FColor::Cyan, 3.0f, "Initializing all entities");
			InitializeAllEntities();
		}
		else {
			NLogger::Message(FColor::Cyan, 3.0f, "Restarting round");
			RestartRound();
		}
		m_tNextRoundRestart = FLT_MAX;
	}

	for (eindex i = 0; i < g_ppEntityListSmall->Num(); i++) {
		(*g_ppEntityListSmall)[i]->DefaultThink();
	}

	for (eindex i = 0; i < g_ppEntityListSmall->Num(); i++) {
		(*g_ppEntityListSmall)[i]->Think();
	}
}

void AGameRules::BeginPlay() {
	BaseClass::BeginPlay();
	Msg("AGameRules::BeginPlay\n");
	Msg("ReadyEntityCount = %i/%i/%i\n", s_iReadyEntityCount, g_ppEntityListSmall->Num(), s_iEntityCount);
	for (int i = 0; i < g_ppEntityListSmall->Num(); i++) {
		FString name = (*g_ppEntityListSmall)[i]->GetActor()->GetName();
		NLogger::Message(name);
	}
	
	m_bHasRestartedRound = false;
	m_bHasInitializedAllEntities = false;


	m_tNextRoundRestart = -FLT_MAX;
}

void AGameRules::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Msg(__FUNCTION__);
	m_bHasInitializedAllEntities = false;
	g_pGlobals->markReset();
}

void AGameRules::RestartRound() {
	Msg(__FUNCTION__);

	//we need to do this right, otherwise when we iterate through
	//the entity list, the size of the list might change
	TArray<EHANDLE> m_aDestroyedEntities;
	//this array remembers which entities we'll destroy later

	for (int i = 0; i < g_ppEntityListSmall->Num(); i++) {
		IBaseEntity* pEnt = (*g_ppEntityListSmall)[i];

		//ignore entities marked with preserve
		if (!pEnt->HasFlags(FL_ROUND_PRESERVE)) {

			//remember entities which need destruction
			if (pEnt->HasFlags(FL_ROUND_DESTROY)) {
				m_aDestroyedEntities.Add(pEnt->GetEHandle());
				continue;
			}
			else
				pEnt->Respawn();
		}
	}

	//now destroy everything marked in the list
	while (m_aDestroyedEntities.Num() > 0) {
		EHANDLE ent = m_aDestroyedEntities[0];
		ent->DestroyEntity();
		m_aDestroyedEntities.RemoveAt(0);
	}
}

void AGameRules::InitializeAllEntities() {
	Msg(__FUNCTION__);
	//run pre inits of all entities
	for (eindex i = 0; i < g_ppEntityListSmall->Num(); i++) {
		(*g_ppEntityListSmall)[i]->SetNextThink(FLT_MIN);
		(*g_ppEntityListSmall)[i]->PreInit();
	}

	//run global initializers in order
	CStaticInitializer::InvokeAllInOrder();

	//run post inits of all entities
	for (eindex i = 0; i < g_ppEntityListSmall->Num(); i++)
		(*g_ppEntityListSmall)[i]->PreInit();

	//mark us as ready
	m_bHasInitializedAllEntities = true;
}