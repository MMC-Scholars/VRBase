

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
#include "AGameRules/AGameRules.h"
#include "System/Input.h"
#include "ABasePawn.generated.h"

UCLASS()
class VRBASE_API ABasePawn : public APawn, public IBaseEntity {

//------------------------------------------------------------------------------
// ACTOR/PAWN/ENTITY OVERRIDES
//------------------------------------------------------------------------------
	GENERATED_BODY()

public:
	ABasePawn();

	virtual void BeginPlay() override {
		g_pGlobals->checkReset();
		APawn::BeginPlay();
		ReportReady();

		//If the game's already started, call initializations 
		if (g_pGameRules && g_pGameRules->GameReady()) {
			PreInit();
			PostInit();
		}
	}

	virtual void Tick(float deltaTime) override {}
	virtual void PostDuplicate(EDuplicateMode::Type mode) override {
		Super::PostDuplicate(mode);
		IBaseEntity::PostDuplicate(mode);
	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PreInit() override;

	virtual void SetControllerClass(UClass* LControllerClass, UClass* RControllerClass);

//------------------------------------------------------------------------------
// MEMBER VARIABLES FOR PLAYER/PAWN/VR SETUP
//-----------------------------------------------------------------------------
public:
	// Components
	UCapsuleComponent*			m_pRootCapsule;
	USceneComponent*			m_pPlayerRoot;
	UCameraComponent*			m_pCamera;
	UMotionControllerComponent* m_pLMotionController;
	UChildActorComponent*		m_pLChildActor;
	UMotionControllerComponent* m_pRMotionController;
	UChildActorComponent*		m_pRChildActor;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller Classes")
	UClass* m_pLControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller Classes")
	UClass* m_pRControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Controllers)
	UStaticMesh*				m_pLeftControllerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Controllers)
	UStaticMesh*				m_pRightControllerMesh;

	ABaseController*			m_pLHand;
	ABaseController*			m_pRHand;


// set controller classes dynamically from within the editor
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

		FName PropertyName = (PropertyChangedEvent.Property != nullptr)
			? PropertyChangedEvent.Property->GetFName() : NAME_None;

		if (m_pLControllerClass && m_pRControllerClass) {

			SetControllerClass(m_pLControllerClass, m_pRControllerClass);
			
		}

		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif


//------------------------------------------------------------------------------
// INPUT FUNCTIONS / INPUT HANDLING
//-----------------------------------------------------------------------------
#define KEY_INPUT(key, change, hand) \
	void On##hand##_##key##_##change() { \
		if (m_p##hand##Hand == NULL) { \
			NLogger::Warning("ABasePawn hand is NULL"); \
			return; \
		} \
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

	//Controller input for "use"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationParams m_leftControllerInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationParams m_rightControllerInput;

	//These overrides expose our UPROPERTY variables to IBaseEntity
	virtual FEntityInputRegistrationParams*	GetLeftControllerInputRegistrationParams() { return &m_leftControllerInput; }
	virtual FEntityInputRegistrationParams*	GetRightControllerInputRegistrationParams() { return &m_rightControllerInput; }


//------------------------------------------------------------------------------
// PLAYER TELEPORT HANDLING
//-----------------------------------------------------------------------------

	bool CanTeleportToLocation(const FVector& loc);

	bool TeleportPlayer(const FVector& loc, const FRotator& rot);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportation")
		AActor* m_pTeleportBounds;
};