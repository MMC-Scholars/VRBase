#pragma once

#include "ABaseController/ABaseController.h"
#include "AGameRules/AGameRules.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/TextRenderComponent.h"
//#include "CoreMinimal.h"
#include "FPawnInstruction.h"
#include "GameFramework/Pawn.h"
//#include "HeadMountedDisplay.h"
//#include "IBaseEntity/IBaseEntity.h"
#include "MotionControllerComponent.h"
//#include "System/Input.h"
#include "System/NLogger.h"

#include "ABasePawn.generated.h"

UCLASS()
class VRBASE_API ABasePawn : public APawn, public IBaseEntity {
    GENERATED_BODY()

public:
    ABasePawn();

    virtual void BeginPlay() override {
        g_pGlobals->checkReset();
        APawn::BeginPlay();
        ReportReady();

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
    virtual void
    SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void PreInit() override;
    virtual void DefaultThink() override;

    virtual void SetControllerClass(UClass* LControllerClass,
                                    UClass* RControllerClass);

    //-------------------------------------------------------------------------------------
    // Member variables for player/pawn setup
    //-------------------------------------------------------------------------------------

public:
    UCapsuleComponent*          m_pRootCapsule;
    USceneComponent*            m_pPlayerRoot;
    UCameraComponent*           m_pCamera;
    UMotionControllerComponent* m_pLMotionController;
    UChildActorComponent*       m_pLChildActor;
    UMotionControllerComponent* m_pRMotionController;
    UChildActorComponent*       m_pRChildActor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Left Controller",
              DisplayName = "Controller Class")
    UClass* m_pLControllerClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Right Controller",
              DisplayName = "Controller Class")
    UClass* m_pRControllerClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Left Controller",
              DisplayName = "Controller Mesh")
    UStaticMesh* m_pLeftControllerMesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Right Controller",
              DisplayName = "Controller Mesh")
    UStaticMesh* m_pRightControllerMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controllers",
              DisplayName = "Collision Radius")
    float m_fControllerCollisionRadius;

private:
    ABaseController* m_pLHand;
    ABaseController* m_pRHand;

    //-------------------------------------------------------------------------------------
    // Editor Post Edit properties
    //-------------------------------------------------------------------------------------

#if WITH_EDITOR
    virtual void
    PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

        FName PropertyName = PropertyChangedEvent.Property
                                 ? PropertyChangedEvent.Property->GetFName()
                                 : NAME_None;

        // set controller classes dynamically from within the editor
        if (m_pLControllerClass && m_pRControllerClass)
            SetControllerClass(m_pLControllerClass, m_pRControllerClass);

        Super::PostEditChangeProperty(PropertyChangedEvent);
    }
#endif

    //-------------------------------------------------------------------------------------
    // Input functions and handling
    //-------------------------------------------------------------------------------------

#define KEY_INPUT(key, change, hand)                                                \
    void On##hand##_##key##_##change() {                                            \
        if (m_p##hand##Hand == NULL) {                                              \
            NLogger::Warning("ABasePawn hand is NULL");                             \
            return;                                                                 \
        }                                                                           \
        m_p##hand##Hand->m_iButtons##change |= IN_##key;                            \
        m_p##hand##Hand->OnButtonsChanged();                                        \
    }

public:
    // left input
    KEY_INPUT(TRIGGER, Pressed, L);
    KEY_INPUT(TRIGGER, Released, L);
    KEY_INPUT(GRIP, Pressed, L);
    KEY_INPUT(GRIP, Released, L);
    KEY_INPUT(MENU, Pressed, L);
    KEY_INPUT(MENU, Released, L);
    KEY_INPUT(AX, Pressed, L);
    KEY_INPUT(AX, Released, L);
    KEY_INPUT(BY, Pressed, L);
    KEY_INPUT(BY, Released, L);
    KEY_INPUT(STICK, Pressed, L);
    KEY_INPUT(STICK, Released, L);

    // right input
    KEY_INPUT(TRIGGER, Pressed, R);
    KEY_INPUT(TRIGGER, Released, R);
    KEY_INPUT(GRIP, Pressed, R);
    KEY_INPUT(GRIP, Released, R);
    KEY_INPUT(MENU, Pressed, R);
    KEY_INPUT(MENU, Released, R);
    KEY_INPUT(AX, Pressed, R);
    KEY_INPUT(AX, Released, R);
    KEY_INPUT(BY, Pressed, R);
    KEY_INPUT(BY, Released, R);
    KEY_INPUT(STICK, Pressed, R);
    KEY_INPUT(STICK, Released, R);

    // virtual void UpdateInput(float);
    // virtual void UpdateTouch(ETouchIndex::Type, FVector);
    // https://api.unrealengine.com/INT/API/Runtime/InputCore/ETouchIndex__Type/index.html

    // "Use" controller input
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    FEntityInputRegistrationParams m_leftControllerInput;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    FEntityInputRegistrationParams m_rightControllerInput;

    // These overrides expose our UProperty variables to IBaseEntity
    virtual FEntityInputRegistrationParams*
    GetLeftControllerInputRegistrationParams() {
        return &m_leftControllerInput;
    }
    virtual FEntityInputRegistrationParams*
    GetRightControllerInputRegistrationParams() {
        return &m_rightControllerInput;
    }

    //-------------------------------------------------------------------------------------
    // Teleport handling
    //-------------------------------------------------------------------------------------

public:
    bool IsWithinTeleportBounds(const FVector& loc, const FVector& bOrigin,
                                const FVector& bExtent);
    bool CanTeleportToLocation(const FVector& loc);
    bool TeleportPlayer(const FVector& loc, const FRotator& rot);
    bool TeleportPlayerRelative(const FVector& loc, const FRotator& rot);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportation",
              DisplayName = "Teleportation Enabled")
    bool m_bTeleportationEnabled;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportation",
              DisplayName = "Teleportation Bounds")
    TArray<AActor*> m_aTeleportBounds;

    //-------------------------------------------------------------------------------------
    // Controller instructions
    //-------------------------------------------------------------------------------------

private:
    FPawnInstruction* m_sInstr;

public:
    ftime                 m_tInstrChangeTime;
    UTextRenderComponent* m_pRTextInstr;
    UTextRenderComponent* m_pLTextInstr;

    UPROPERTY(EditAnywhere, Category = "Instructions",
              DisplayName = "Pawn Instructions")
    TArray<FPawnInstruction> m_aInstr;

    void SetInstruction(FPawnInstruction instr);
    void NextInstruction();
};
