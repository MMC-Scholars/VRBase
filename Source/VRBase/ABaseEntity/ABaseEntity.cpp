// Fill out your copyright notice in the Description page of Project Settings.

#include "ABaseEntity.h"
#include "AGameRules/AGameRules.h"
#include "ABaseController/ABaseController.h"

ABaseEntity::ABaseEntity() : IBaseEntity() {
	
	Tags.Add(TAG_BASEENTITY);
	m_pSelfAsActor = this;
	bAllowTickBeforeBeginPlay = false;
	SetActorTickEnabled(false);
	
	m_flUseMaxRadius = FLT_MAX;
}

void ABaseEntity::BeginPlay() {
	g_pGlobals->checkReset();
	AActor::BeginPlay();
	ReportReady();

	//If the game's already started, call initializations 
	if (g_pGameRules && g_pGameRules->GameReady()) {
		PreInit();
		PostInit();
	}
}

bool ABaseEntity::IsUseableBy(const ABaseController* pController) const {
	return GetSquaredDistanceTo(pController) < sqr(m_flUseMaxRadius);
}