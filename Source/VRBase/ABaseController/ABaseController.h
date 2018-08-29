// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ABaseController.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API ABaseController : public ABaseEntity {
	GENERATED_BODY()
	
	ABaseController();

	// Components
	USceneComponent*		m_pHandScene;
	UStaticMeshComponent*	m_pHandMeshComponent;
	USphereComponent*		m_pControllerCollision;

	// Variables
	EControllerHand*		m_pWhichHand;
	//TArray<AActor*>		m_aOverlapActors;
	//TArray<APickup*>		m_aAttachActors;

	// Events
	//UFUNCTION()
	//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Functions
	void setWhichHand(EControllerHand h);
	
};
