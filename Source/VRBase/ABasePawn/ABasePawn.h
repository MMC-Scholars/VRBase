// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IBaseEntity/IBaseEntity.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "Components/ChildActorComponent.h"

#include "ABaseController/ABaseController.h"
#include "ABasePawn.generated.h"

UCLASS()
class VRBASE_API ABasePawn : public APawn, public IBaseEntity {
//class VRBASE_API ABasePawn : public APawn {
	GENERATED_BODY()

	ABasePawn();

	virtual void BeginPlay() override {
		g_pGlobals->checkReset();
		APawn::BeginPlay();
		s_iReadyEntityCount++;
	}

	virtual void Tick(float deltaTime) override {}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PreInit() override;

	// Components
	UCapsuleComponent*			m_pRootCapsule;
	USceneComponent*			m_pPlayerRoot;
	UCameraComponent*			m_pCamera;
	UMotionControllerComponent* m_pLMotionController;
	UChildActorComponent*		m_pLChildActor;
	UMotionControllerComponent* m_pRMotionController;
	UChildActorComponent*		m_pRChildActor;

	// Variables
	ABaseController*			m_pLHand;
	ABaseController*			m_pRHand;


};
