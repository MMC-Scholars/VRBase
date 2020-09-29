#pragma once

#include "APickup/APickup.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
//#include "CoreMinimal.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "LineTools/linetools.h"
#include "ProceduralMeshComponent.h"
#include "System/Input.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"

#include "ABaseController.generated.h"

UCLASS()
class VRBASE_API ABaseController : public ABaseEntity {
    GENERATED_BODY()

private:
    FRotator m_rTeleportationRot;

public:
    ABaseController();

    USceneComponent*          m_pHandScene;
    UStaticMeshComponent*     m_pHandMeshComponent;
    USphereComponent*         m_pControllerCollision;
    UProceduralMeshComponent* m_pProcMeshComponent;

    ABasePawn* m_pOwnerPawn;

    EControllerHand  m_eWhichHand;
    bool             m_bPerformedPositionFixup;
    TArray<AActor*>  m_aOverlapActors;
    TArray<APickup*> m_aAttachActors;

    bool m_bTeleportationActive;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
    TArray<SEntityInputTriggerRequirement>
        m_aRegisteredEntities; // which entites are listening to buttons on this
                               // controller?

public:
    uint32       m_iButtons;         // which buttons are currently being pressed?
    uint32       m_iButtonsPressed;  // which buttons were just pressed?
    uint32       m_iButtonsReleased; // which buttons were just released?
    virtual void OnButtonsChanged();

    uint32 ButtonsPressed() const {
        return m_iButtons;
    } // returns bitfield of buttons currently pressed on this controller
    void RegisterEntityInput(IBaseEntity*, uint32 iButton, bool bOnReleased);
    void SetWhichHand(EControllerHand);

    void SetStaticMesh(UStaticMesh*);

    // called when holding the teleport button
    void OnUsed(ABaseEntity* pActivator) override;

    // casts a spline and circle while holding the teleport button
    void DefaultThink() override;

    // returns a null-terminated list of actors to ignored when raytracing for
    // teleportation
    void GetTraceIgnoredActors(TArray<AActor*>&);

    // retrieves the controller which is not this one
    inline ABaseController* OtherController() {
        return this == g_pLeftController ? g_pRightController : g_pLeftController;
    }
};

extern ABaseController* g_pLeftController;
extern ABaseController* g_pRightController;
inline bool ControllersReady() { return g_pRightController && g_pLeftController; }
