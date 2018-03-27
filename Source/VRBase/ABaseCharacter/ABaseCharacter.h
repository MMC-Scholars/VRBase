// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABaseCharacter.generated.h"

UCLASS()
class VRBASE_API ABaseCharacter : public ACharacter, public IBaseEntity
{
	GENERATED_BODY()

	ABaseCharacter() {
		Tags.Add(TAG_BASECHARACTER);
		m_pSelfAsActor = this;
		bAllowTickBeforeBeginPlay = false;
		SetActorTickEnabled(false);
	}

	//you can override these if you want, but there's no guarantees
	//about how these interact with the new custom game flow
	//for example, BeginPlay() might be called before 
	// g_pGlobals->curtime is correctly set
	virtual void BeginPlay() final override {
		g_pGlobals->checkReset();
		AActor::BeginPlay();
		s_iReadyEntityCount++;
	}
	virtual void Tick(float deltaTime) final override {}
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final override {}
	virtual void SetupPlayerInputComponent(UInputComponent* pComponent) final override;

};
