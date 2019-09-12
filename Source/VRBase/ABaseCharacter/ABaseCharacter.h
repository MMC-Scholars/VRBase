/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABaseCharacter.generated.h"

UCLASS()
class VRBASE_API ABaseCharacter : public ACharacter, public IBaseEntity {
	GENERATED_BODY()

	ABaseCharacter() {
		Tags.Add(TAG_BASECHARACTER);
		m_pSelfAsActor = this;
		bAllowTickBeforeBeginPlay = false;
		SetActorTickEnabled(false);
	}

	virtual void BeginPlay() final override {
		g_pGlobals->checkReset();
		AActor::BeginPlay();
		ReportReady();
	}
	virtual void Tick(float deltaTime) final override {}
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final override {}
	virtual void SetupPlayerInputComponent(UInputComponent* pComponent) final override;

};
