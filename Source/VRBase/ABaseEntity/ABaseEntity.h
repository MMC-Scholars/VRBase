// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABaseEntity.generated.h"

//-------------------------------------------------------------------------------------
// This is our master base class for anything that is not controlled by the player.
// I.e. anything that is not an APawn or an ACharacter
//-------------------------------------------------------------------------------------
UCLASS()
class VRBASE_API ABaseEntity : public AActor, public IBaseEntity
{
public:
	DECLARE_CLASS_SIMPLE(ABaseEntity, IBaseEntity)
	GENERATED_BODY()

		//not much to do here because most of the functionality is built into
		//the IBaseEntity interface
	ABaseEntity() : IBaseEntity() {
		Tags.Add(TAG_BASEENTITY); 
		m_pSelfAsActor = this;
		bAllowTickBeforeBeginPlay = false;
		SetActorTickEnabled(false);
	}

	//you can override these if you want, but there's no guarantees
	//about how these interact with the new custom game flow
	//for example, BeginPlay() might be called before 
	// g_pGlobals->curtime is correctly set
	virtual void BeginPlay() override {
		g_pGlobals->checkReset();
		AActor::BeginPlay();
		s_iReadyEntityCount++;
	}

	virtual void Tick(float deltaTime) override {  }
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override {}
	virtual void PostDuplicate(EDuplicateMode::Type mode) override {
		Super::PostDuplicate(mode);
		IBaseEntity::PostDuplicate(mode);
	}
};
