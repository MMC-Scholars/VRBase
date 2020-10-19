#include "ABasePawn.h"
#include "IXRTrackingSystem.h"
#define DEFAULT_CONTROLLER_CLASS ABaseController
#define CAPSULE_HEIGHT           96.0

ABasePawn::ABasePawn() {
    Tags.Add(TAG_BASEPAWN);
    m_pSelfAsActor = this;

    m_pLHand = NULL;
    m_pRHand = NULL;

    // controller default class is ABaseController
    m_pLControllerClass = DEFAULT_CONTROLLER_CLASS::StaticClass();
    m_pRControllerClass = DEFAULT_CONTROLLER_CLASS::StaticClass();

    // disable event tick
    bAllowTickBeforeBeginPlay = false;
    SetActorTickEnabled(false);

    // Root Component Capsule
    m_pRootCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
    m_pRootCapsule->InitCapsuleSize(16.0, CAPSULE_HEIGHT);
    RootComponent = m_pRootCapsule;

    // Player Root Scene Component
    m_pPlayerRoot = CreateDefaultSubobject<USceneComponent>("Player Root");
    m_pPlayerRoot->SetupAttachment(RootComponent);

    // HMD Camera
    m_pCamera             = CreateDefaultSubobject<UCameraComponent>("Camera");
    m_pCamera->bLockToHmd = true;
    m_pCamera->SetupAttachment(m_pPlayerRoot);

    // L Motion Controller
    m_pLMotionController =
        CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
    m_pLMotionController->SetTrackingSource(EControllerHand::Left);
    m_pLMotionController->SetupAttachment(m_pPlayerRoot);

    // L Child Actor
    m_pLChildActor =
        CreateDefaultSubobject<UChildActorComponent>("Left Child Actor");
    m_pLChildActor->SetChildActorClass(DEFAULT_CONTROLLER_CLASS::StaticClass());
    m_pLChildActor->SetupAttachment(m_pLMotionController);

    // R Motion Controller
    m_pRMotionController = CreateDefaultSubobject<UMotionControllerComponent>(
        "Right Motion Controller");
    m_pRMotionController->SetTrackingSource(EControllerHand::Right);
    m_pRMotionController->SetupAttachment(m_pPlayerRoot);

    // R Child Actor
    m_pRChildActor =
        CreateDefaultSubobject<UChildActorComponent>("Right Child Actor");
    m_pRChildActor->SetChildActorClass(DEFAULT_CONTROLLER_CLASS::StaticClass());
    m_pRChildActor->SetupAttachment(m_pRMotionController);

    // controller collision radii
    m_fControllerCollisionRadius = 12.0f;

    // teleportation enabled
    m_bTeleportationEnabled = true;

    // instructions
    float instrScale = 0.1;

    // L text instructions
    m_pLTextInstr =
        CreateDefaultSubobject<UTextRenderComponent>("Left Text Instructions");
    m_pLTextInstr->SetupAttachment(m_pLChildActor);
    m_pLTextInstr->SetXScale(instrScale);
    m_pLTextInstr->SetYScale(instrScale);
    m_pLTextInstr->SetHorizontalAlignment(EHTA_Center);
    m_pLTextInstr->SetVerticalAlignment(EVRTA_TextBottom);
    m_pLTextInstr->SetWorldRotation(FRotator(0, 180, 0));
    m_pLTextInstr->AddRelativeLocation(FVector(0, 0, 2));
    m_pLTextInstr->SetText(FText::FromString(""));

    // R text instructions
    m_pRTextInstr =
        CreateDefaultSubobject<UTextRenderComponent>("Right Text Instructions");
    m_pRTextInstr->SetupAttachment(m_pRChildActor);
    m_pRTextInstr->SetXScale(instrScale);
    m_pRTextInstr->SetYScale(instrScale);
    m_pRTextInstr->SetHorizontalAlignment(EHTA_Center);
    m_pRTextInstr->SetVerticalAlignment(EVRTA_TextBottom);
    m_pRTextInstr->SetWorldRotation(FRotator(0, 180, 0));
    m_pRTextInstr->AddRelativeLocation(FVector(0, 0, 2));
    m_pRTextInstr->SetText(FText::FromString(""));

    // default instructions
    m_aInstr.Add(FPawnInstruction(
        "Press and hold the A or X buttons to teleport on Oculus Rift"));
    m_aInstr.Add(FPawnInstruction("While teleporting rotate your wrist to "
                                  "indicate the teleportation direction"));
    m_aInstr.Add(FPawnInstruction("Press the index finger triggers near objects "
                                  "to pick them up or interact"));

    // automatically possess pawn placed in world instead of generating a pawn
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

//-------------------------------------------------------------------------------------
// Input
//-------------------------------------------------------------------------------------

// bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (PlayerInputComponent) {

		// OCULUS TOUCH KEY BINDINGS //
		
        // left input

        // Trigger
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Trigger_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_TRIGGER_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Trigger_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_TRIGGER_Released);
        // Grip
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Grip_Click, IE_Pressed,
                                      this, &ABasePawn::OnL_GRIP_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Grip_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_GRIP_Released);
        // Menu Button
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Menu_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_MENU_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Menu_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_MENU_Released);
        // X
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_X_Click,
                                      IE_Pressed, this, &ABasePawn::OnL_AX_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_X_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_AX_Released);
        // Y
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Y_Click,
                                      IE_Pressed, this, &ABasePawn::OnL_BY_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Y_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_BY_Released);
        // Thumbstick
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Thumbstick_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_STICK_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Left_Thumbstick_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_STICK_Released);

        // right input

        // Trigger
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Trigger_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_TRIGGER_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Trigger_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_TRIGGER_Released);
        // Grip
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Grip_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_GRIP_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Grip_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_GRIP_Released);
        // Menu Button
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_System_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_MENU_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_System_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_MENU_Released);
        // A
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_A_Click,
                                      IE_Pressed, this, &ABasePawn::OnR_AX_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_A_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_AX_Released);
        // B
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_B_Click,
                                      IE_Pressed, this, &ABasePawn::OnR_BY_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_B_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_BY_Released);
        // Thumbstick
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Thumbstick_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_STICK_Pressed);
        PlayerInputComponent->BindKey(EKeys::OculusTouch_Right_Thumbstick_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_STICK_Released);

		// HTC VIVE KEY BINDINGS //

		// left input

        // Trigger
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trigger_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_TRIGGER_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trigger_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_TRIGGER_Released);
        // Grip
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Grip_Click, IE_Pressed,
                                      this, &ABasePawn::OnL_GRIP_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Grip_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_GRIP_Released);
        // Menu Button
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Menu_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_MENU_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Menu_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_MENU_Released);
        // X
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Left,
                                      IE_Pressed, this, &ABasePawn::OnL_AX_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Left,
                                      IE_Released, this,
                                      &ABasePawn::OnL_AX_Released);
        // Y
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Right,
                                      IE_Pressed, this, &ABasePawn::OnL_BY_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Right,
                                      IE_Released, this,
                                      &ABasePawn::OnL_BY_Released);
        // Thumbstick
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnL_STICK_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Left_Trackpad_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnL_STICK_Released);

        // right input

        // Trigger
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trigger_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_TRIGGER_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trigger_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_TRIGGER_Released);
        // Grip
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Grip_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_GRIP_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Grip_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_GRIP_Released);
        // Menu Button
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Menu_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_MENU_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Menu_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_MENU_Released);
        // A
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Right,
                                      IE_Pressed, this, &ABasePawn::OnR_AX_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Right,
                                      IE_Released, this,
                                      &ABasePawn::OnR_AX_Released);
        // B
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Left,
                                      IE_Pressed, this, &ABasePawn::OnR_BY_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Left,
                                      IE_Released, this,
                                      &ABasePawn::OnR_BY_Released);
        // Thumbstick
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Click,
                                      IE_Pressed, this,
                                      &ABasePawn::OnR_STICK_Pressed);
        PlayerInputComponent->BindKey(EKeys::Vive_Right_Trackpad_Click,
                                      IE_Released, this,
                                      &ABasePawn::OnR_STICK_Released);

        // TODO touch events?
        // PlayerInputComponent->BindTouch(IE_Pressed, this,
        // &ABasePawn::UpdateTouch(ETouchIndex::Type, FVector);

        // TODO axis events?
        // PlayerInputComponent->BindAxisKey(EKeys::MotionController_Left_Thumbstick_X,
        // this, &ABasePawn::UpdateInput);
    }
}

ABasePawn* g_pBasePawn = NULL;
void       ABasePawn::PreInit() {
    g_pBasePawn = this;

    // set tracking origin to floor
    auto HMD = GEngine->XRSystem.Get();
    if (HMD)
        HMD->SetTrackingOrigin(EHMDTrackingOrigin::Floor);
    else
        NLogger::Warning("Failed to initialize HMD!");

    FVector loc = GetActorLocation();
    SetActorLocation(FVector(loc.X, loc.Y, loc.Z - CAPSULE_HEIGHT));

    SetControllerClass(m_pLControllerClass, m_pRControllerClass);

    m_rightControllerInput = FEntityInputRegistrationParams();
    m_leftControllerInput  = FEntityInputRegistrationParams();

    // display first instruction
    if (m_aInstr.Num()) SetInstruction(m_aInstr[0]);

    // initial world transform (rotation, location, scale)
    m_tInitialTransform = FTransform(m_pRootCapsule->GetComponentRotation(),
                                     GetActorLocation(), GetActorScale());

    // move HMD to actual player start location
    TeleportPlayer(getInitialLocation(), getInitialRotation());
}

void ABasePawn::SetControllerClass(UClass* LControllerClass,
                                   UClass* RControllerClass) {
    if (LControllerClass && RControllerClass) {

        // set child actors
        m_pLChildActor->SetChildActorClass(LControllerClass);
        m_pRChildActor->SetChildActorClass(RControllerClass);

        // casts to ABaseController
        m_pLHand = Cast<DEFAULT_CONTROLLER_CLASS>(m_pLChildActor->GetChildActor());
        if (m_pLHand) {
            m_pLHand->SetWhichHand(EControllerHand::Left);
            m_pLHand->SetStaticMesh(m_pLeftControllerMesh);
            m_pLHand->m_pOwnerPawn = this;
            if (m_pLHand->m_pControllerCollision)
                m_pLHand->m_pControllerCollision->SetSphereRadius(
                    m_fControllerCollisionRadius);

            if (m_pLeftControllerMesh)
                m_pLHand->m_pProcMeshComponent->SetVisibility(false);
            else
                m_pLHand->m_pProcMeshComponent->SetVisibility(true);
        }

        m_pRHand = Cast<DEFAULT_CONTROLLER_CLASS>(m_pRChildActor->GetChildActor());
        if (m_pRHand) {
            m_pRHand->SetWhichHand(EControllerHand::Right);
            m_pRHand->SetStaticMesh(m_pRightControllerMesh);
            m_pRHand->m_pOwnerPawn = this;
            if (m_pRHand->m_pControllerCollision)
                m_pRHand->m_pControllerCollision->SetSphereRadius(
                    m_fControllerCollisionRadius);

            if (m_pRightControllerMesh)
                m_pRHand->m_pProcMeshComponent->SetVisibility(false);
            else
                m_pLHand->m_pProcMeshComponent->SetVisibility(true);
        }

        if (m_pLHand && m_pRHand) {
            m_pLHand->m_leftControllerInput  = m_leftControllerInput;
            m_pRHand->m_rightControllerInput = m_rightControllerInput;
        }
    }
}

//-------------------------------------------------------------------------------------
// Teleportation
//-------------------------------------------------------------------------------------

bool ABasePawn::IsWithinTeleportBounds(const FVector& loc, const FVector& bOrigin,
                                       const FVector& bExtent) {
    // this is what APawn::IsInsideOrOn() should compute but (for an unknown
    // reason) it returns a different answer than expected
    return (loc.X >= bOrigin.X - bExtent.X && loc.X <= bOrigin.X + bExtent.X &&
            loc.Y >= bOrigin.Y - bExtent.Y && loc.Y <= bOrigin.Y + bExtent.Y &&
            loc.Z >= bOrigin.Z - bExtent.Z && loc.Z <= bOrigin.Z + bExtent.Z);
}

bool ABasePawn::CanTeleportToLocation(const FVector& loc) {
    // if no bounds exist return true
    if (!m_aTeleportBounds.Num()) return true;

    bool    bLocValid = false;
    FVector boxOrigin, boxExtent;
    int     i = 0;

    // use a while loop to ensure loop runs <= n times
    while (i < m_aTeleportBounds.Num() && !bLocValid) {
        // if within bounds
        if (m_aTeleportBounds[i]) {
            m_aTeleportBounds[i]->GetActorBounds(false, boxOrigin, boxExtent);
            bLocValid =
                bLocValid || IsWithinTeleportBounds(loc, boxOrigin, boxExtent);
        }
        i++;
    }

    return bLocValid;
}

bool ABasePawn::TeleportPlayer(const FVector& loc, const FRotator& rot) {
    if (!CanTeleportToLocation(loc)) return false;

    // location
    FVector lPrev = GetActorLocation();
    FVector lHMD  = m_pCamera->GetComponentLocation();
    SetActorLocation(
        FVector(lPrev.X - lHMD.X + loc.X, lPrev.Y - lHMD.Y + loc.Y, lPrev.Z));

    // rotation
    FRotator rPrev = GetActorRotation();
    FRotator rHMD  = m_pCamera->GetComponentRotation();
    SetActorRotation(
        FRotator(rPrev.Pitch, rPrev.Yaw - rHMD.Yaw + rot.Yaw, rPrev.Roll));

    return true;
}

bool ABasePawn::TeleportPlayerRelative(const FVector& loc, const FRotator& rot) {
    if (!CanTeleportToLocation(loc)) return false;

    // location
    FVector lPrev = GetActorLocation();
    FVector lHMD  = m_pCamera->GetComponentLocation();
    SetActorRelativeLocation(
        FVector(lPrev.X - lHMD.X + loc.X, lPrev.Y - lHMD.Y + loc.Y, lPrev.Z));

    // rotation
    FRotator rPrev = GetActorRotation();
    FRotator rHMD  = m_pCamera->GetComponentRotation();
    SetActorRotation(
        FRotator(rPrev.Pitch, rPrev.Yaw - rHMD.Yaw + rot.Yaw, rPrev.Roll));

    return true;
}

//-------------------------------------------------------------------------------------
// Instructions
//-------------------------------------------------------------------------------------

void ABasePawn::SetInstruction(FPawnInstruction instr) {
    UTextRenderComponent* component;

    // left hand
    if (instr.hand == EControllerHand::Left) {
        component = m_pLTextInstr;
        m_pRTextInstr->SetText(FText::FromString(""));
    }

    // right hand
    else {
        component = m_pRTextInstr;
        m_pLTextInstr->SetText(FText::FromString(""));
    }

    component->SetText(instr.text);
    component->SetTextRenderColor(instr.color);

    if (!instr.changeOnButtonPress)
        m_tInstrChangeTime = g_pGlobals->curtime + instr.timedChange;

    m_sInstr = &instr;
}

void ABasePawn::NextInstruction() {
    if (m_aInstr.Num() > 1) { // verify there is an instruction to switch to
        SetInstruction(m_aInstr[1]);
        m_sInstr = &m_aInstr[1];
        m_aInstr.RemoveAt(0);
    } else { // clear instructions if no instructions exist
        m_pLTextInstr->SetText(FText::FromString(""));
        m_pRTextInstr->SetText(FText::FromString(""));
        m_sInstr = nullptr;
    }
}

void ABasePawn::DefaultThink() {
    // change instruction in timely manner
    if (m_sInstr && !m_sInstr->changeOnButtonPress) {
        if (g_pGlobals->curtime - m_tInstrChangeTime >= 0) NextInstruction();
    }
}