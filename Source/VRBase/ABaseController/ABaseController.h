

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "System/Input.h"
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
	EControllerHand			m_pWhichHand;
	//TArray<AActor*>		m_aOverlapActors;
	//TArray<APickup*>		m_aAttachActors;

	// Events
	//UFUNCTION()
	//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	TArray<SEntityInputTriggerRequirement> m_aRegisteredEntities; //Which entites are listening to buttons on this controller?

	uint32 m_iButtons; //bitfield - which buttons are currently being pressed?
	uint32 m_iButtonsPressed; //bitifield - which buttons were just pressed?
	uint32 m_iButtonsReleased; //bitfield - which buttons were just released?
	void OnButtonsChanged();


public:
	uint32 ButtonsPressed() const { return m_iButtons; } //Returns bitfield of buttons currently pressed on this controller
	void RegisterEntityInput(IBaseEntity*, uint32 iButton, bool bOnReleased);
	void SetWhichHand(EControllerHand);
	
	void SetStaticMesh(UStaticMesh*);
};

extern ABaseController* g_pLeftController;
extern ABaseController* g_pRightController;
inline bool ControllersReady() {
	return g_pRightController && g_pLeftController;
}
