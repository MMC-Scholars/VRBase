

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "System/Input.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "APickup/APickup.h"
#include "ABaseController.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API ABaseController : public ABaseEntity {
	GENERATED_BODY()
	
public:
	ABaseController();

	// Components
	USceneComponent*		m_pHandScene;
	UStaticMeshComponent*	m_pHandMeshComponent;
	USphereComponent*		m_pControllerCollision;

	ABasePawn*				m_pOwnerPawn;

	// Variables
	EControllerHand			m_eWhichHand;
	bool					m_bPerformedPositionFixup;
	TArray<AActor*>			m_aOverlapActors;
	TArray<APickup*>		m_aAttachActors;
	bool					m_bTeleportationActive;
	FRotator				m_rTeleportationRot;

	// Events
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	TArray<SEntityInputTriggerRequirement> m_aRegisteredEntities; //Which entites are listening to buttons on this controller?

public:
	uint32 m_iButtons; //bitfield - which buttons are currently being pressed?
	uint32 m_iButtonsPressed; //bitifield - which buttons were just pressed?
	uint32 m_iButtonsReleased; //bitfield - which buttons were just released?
	virtual void OnButtonsChanged();



	uint32 ButtonsPressed() const { return m_iButtons; } //Returns bitfield of buttons currently pressed on this controller
	void RegisterEntityInput(IBaseEntity*, uint32 iButton, bool bOnReleased);
	void SetWhichHand(EControllerHand);
	
	void SetStaticMesh(UStaticMesh*);


	//These are called when we hold the teleport button
	void OnUsed(ABaseEntity* pActivator) override;

	//This will cast a spline and circle while we are holding the button
	void DefaultThink() override;

	// Returns a null-terminated list of actors to ignored when raytracing for teleportation
	void GetTraceIgnoredActors(TArray<AActor*>&);

	//Retrieves the controller which is not this one
	inline ABaseController* OtherController() {
		return this == g_pLeftController ? g_pRightController : g_pLeftController;
	}
};

extern ABaseController* g_pLeftController;
extern ABaseController* g_pRightController;
inline bool ControllersReady() {
	return g_pRightController && g_pLeftController;
}
