#ifndef CBASEPAWN_H
#define CBASEPAWN_H
#include "IBaseEntity/IBaseEntity.h"
#include "UnrealEngine.h"

class CBasePawn : public IBaseEntity, public APawn {
	CBasePawn() {
		Tags.Add(TAG_BASEPAWN);
		m_pSelfAsActor = this;
	}

	virtual void BeginPlay() override {
		Respawn();
	}
	virtual void Tick(float deltaTime) override {}
};

#endif //CBASEPAWN_H 
