// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "System/predefs.h"
#include "IBaseEntity/IBaseEntity.h"

//-------------------------------------------------------------------------------------
// This is our master base class for anything that is not controlled by the player.
// I.e. anything that is not an APawn or an ACharacter
//-------------------------------------------------------------------------------------
class CBaseEntity : public AActor, public IBaseEntity {
	//not much to do here because most of the functionality is built into
	//the IBaseEntity interface
	CBaseEntity() {}

	virtual void BeginPlay() override {
		Respawn();
	}
	virtual void Tick(float deltaTime) override {}
};


#endif //CBASEENTITY_H