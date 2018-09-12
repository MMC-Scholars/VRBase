

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
#include "System/Input.h"
#include "ABasePawn.generated.h"

UCLASS()
class VRBASE_API ABasePawn : public APawn, public IBaseEntity {

	GENERATED_BODY()

	ABasePawn();

	virtual void BeginPlay() override {
		g_pGlobals->checkReset();
		APawn::BeginPlay();
		s_iReadyEntityCount++;
		ReportReady();
	}

	virtual void Tick(float deltaTime) override {}
	virtual void PostDuplicate(EDuplicateMode::Type mode) override {
		Super::PostDuplicate(mode);
		IBaseEntity::PostDuplicate(mode);
	}

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


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Controllers)
	UStaticMesh*				m_pLeftControllerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Controllers)
	UStaticMesh*				m_pRightControllerMesh;

	// Variables
	ABaseController*			m_pLHand;
	ABaseController*			m_pRHand;

// Key input functions
#define KEY_INPUT(key, change, hand) \
	void On##hand##_##key##_##change() { \
		m_p##hand##Hand->m_iButtons##change |= IN_##key; \
		m_p##hand##Hand->OnButtonsChanged(); \
	}

	// Left Input
	
	// Trigger
	KEY_INPUT(TRIGGER, Pressed, L);
	KEY_INPUT(TRIGGER, Released, L);
	// Grip
	KEY_INPUT(GRIP, Pressed, L);
	KEY_INPUT(GRIP, Released, L);
	// Menu Button
	KEY_INPUT(MENU, Pressed, L);
	KEY_INPUT(MENU, Released, L);
	// AX
	KEY_INPUT(AX, Pressed, L);
	KEY_INPUT(AX, Released, L);
	// BY
	KEY_INPUT(BY, Pressed, L);
	KEY_INPUT(BY, Released, L);

	// Right Input

	// Trigger
	KEY_INPUT(TRIGGER, Pressed, R);
	KEY_INPUT(TRIGGER, Released, R);
	// Grip
	KEY_INPUT(GRIP, Pressed, R);
	KEY_INPUT(GRIP, Released, R);
	// Menu Button
	KEY_INPUT(MENU, Pressed, R);
	KEY_INPUT(MENU, Released, R);
	// AX
	KEY_INPUT(AX, Pressed, R);
	KEY_INPUT(AX, Released, R);
	// BY
	KEY_INPUT(BY, Pressed, R);
	KEY_INPUT(BY, Released, R);


	//TODO KEY_INPUT(STICK, Released, R);
	
	//virtual void UpdateInput(float);
	//virtual void UpdateTouch(ETouchIndex::Type, FVector);
	// https://api.unrealengine.com/INT/API/Runtime/InputCore/ETouchIndex__Type/index.html
};
