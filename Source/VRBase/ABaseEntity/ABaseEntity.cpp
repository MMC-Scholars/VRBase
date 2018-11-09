// Fill out your copyright notice in the Description page of Project Settings.

#include "ABaseEntity.h"
#include "ABaseController/ABaseController.h"

ABaseEntity::ABaseEntity() : IBaseEntity() {
	
	Tags.Add(TAG_BASEENTITY);
	m_pSelfAsActor = this;
	bAllowTickBeforeBeginPlay = false;
	SetActorTickEnabled(false);
	
	m_flUseMaxRadius = FLT_MAX;
}

bool ABaseEntity::IsUseableBy(const ABaseController* pController) const {
	return GetSquaredDistanceTo(pController) < sqr(m_flUseMaxRadius);
}