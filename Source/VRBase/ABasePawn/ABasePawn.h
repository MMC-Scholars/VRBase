// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABasePawn.generated.h"

UCLASS()
class VRBASE_API ABasePawn : public APawn, public IBaseEntity
{
	GENERATED_BODY()

	ABasePawn() {
		Tags.Add(TAG_BASEPAWN);
		m_pSelfAsActor = this;
		bAllowTickBeforeBeginPlay = false;
		SetActorTickEnabled(false);
	}

	virtual void BeginPlay() override {
		g_pGlobals->checkReset();
		APawn::BeginPlay();
		s_iReadyEntityCount++;
	}
	virtual void Tick(float deltaTime) override {}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
