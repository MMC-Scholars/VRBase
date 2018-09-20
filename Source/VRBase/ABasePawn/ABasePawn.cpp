

#include "ABasePawn.h"
#include "System/NLogger.h"

#define OCULUS_TOUCH_CONTROLLER_MODEL_LEFT_PATH L"StaticMesh'/Game/Geometry/Controllers/oculus_cv1_controller_left.oculus_cv1_controller_left'"
#define OCULUS_TOUCH_CONTROLLER_MODEL_RIGHT_PATH L"StaticMesh'/Game/Geometry/Controllers/oculus_cv1_controller_right.oculus_cv1_controller_right'"

ABasePawn::ABasePawn() {
	Tags.Add(TAG_BASEPAWN);
	m_pSelfAsActor = this;

	// disable event tick
	bAllowTickBeforeBeginPlay = false;
	SetActorTickEnabled(false);

	// Root Component Capsule
	m_pRootCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	m_pRootCapsule->InitCapsuleSize(16.0, 96.0);
	RootComponent = m_pRootCapsule;

	// Player Root Scene Component
	m_pPlayerRoot = CreateDefaultSubobject<USceneComponent>("Player Root");
	m_pPlayerRoot->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// HMD Camera
	m_pCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_pCamera->bLockToHmd = true;
	m_pCamera->AttachToComponent(m_pPlayerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	// L Motion Controller
	m_pLMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
	m_pLMotionController->Hand = EControllerHand::Left;
	m_pLMotionController->AttachToComponent(m_pPlayerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// L Child Actor
	m_pLChildActor = CreateDefaultSubobject<UChildActorComponent>("Left Child Actor");
	m_pLChildActor->SetChildActorClass(ABaseController::StaticClass());
	m_pLChildActor->AttachToComponent(m_pLMotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// R Motion Controller
	m_pRMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Right Motion Controller");
	m_pRMotionController->Hand = EControllerHand::Right;
	m_pRMotionController->AttachToComponent(m_pPlayerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// R Child Actor
	m_pRChildActor = CreateDefaultSubobject<UChildActorComponent>("Right Child Actor");
	m_pRChildActor->SetChildActorClass(ABaseController::StaticClass());
	m_pRChildActor->AttachToComponent(m_pRMotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


	//Set default controller models
	m_pLeftControllerMesh = FindMesh(OCULUS_TOUCH_CONTROLLER_MODEL_LEFT_PATH);
	m_pRightControllerMesh = FindMesh(OCULUS_TOUCH_CONTROLLER_MODEL_RIGHT_PATH);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (PlayerInputComponent) {
		// Left Input

		// Trigger
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Trigger, IE_Pressed, this, &ABasePawn::OnL_TRIGGER_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Trigger, IE_Released, this, &ABasePawn::OnL_TRIGGER_Released);
		// Grip
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Grip1, IE_Pressed, this, &ABasePawn::OnL_GRIP_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Grip1, IE_Released, this, &ABasePawn::OnL_GRIP_Released);
		// Menu Button
		PlayerInputComponent->BindKey(EKeys::Gamepad_Special_Left, IE_Pressed, this, &ABasePawn::OnL_MENU_Pressed);
		PlayerInputComponent->BindKey(EKeys::Gamepad_Special_Left, IE_Released, this, &ABasePawn::OnL_MENU_Released);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Shoulder, IE_Pressed, this, &ABasePawn::OnL_MENU_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_Shoulder, IE_Released, this, &ABasePawn::OnL_MENU_Released);
		// AX
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_FaceButton1, IE_Pressed, this, &ABasePawn::OnL_AX_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_FaceButton1, IE_Released, this, &ABasePawn::OnL_AX_Released);
		// BY
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_FaceButton2, IE_Pressed, this, &ABasePawn::OnL_BY_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Left_FaceButton2, IE_Released, this, &ABasePawn::OnL_BY_Released);

		// Right Input

		// Trigger
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Trigger, IE_Pressed, this, &ABasePawn::OnR_TRIGGER_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Trigger, IE_Released, this, &ABasePawn::OnR_TRIGGER_Released);
		// Grip
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Grip1, IE_Pressed, this, &ABasePawn::OnR_GRIP_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Grip1, IE_Released, this, &ABasePawn::OnR_GRIP_Released);
		// Menu Button
		PlayerInputComponent->BindKey(EKeys::Gamepad_Special_Right, IE_Pressed, this, &ABasePawn::OnR_MENU_Pressed);
		PlayerInputComponent->BindKey(EKeys::Gamepad_Special_Right, IE_Released, this, &ABasePawn::OnR_MENU_Released);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Shoulder, IE_Pressed, this, &ABasePawn::OnR_MENU_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_Shoulder, IE_Released, this, &ABasePawn::OnR_MENU_Released);
		// AX
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_FaceButton1, IE_Pressed, this, &ABasePawn::OnR_AX_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_FaceButton1, IE_Released, this, &ABasePawn::OnR_AX_Released);
		// BY
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_FaceButton2, IE_Pressed, this, &ABasePawn::OnR_BY_Pressed);
		PlayerInputComponent->BindKey(EKeys::MotionController_Right_FaceButton2, IE_Released, this, &ABasePawn::OnR_BY_Released);


		//TODO PlayerInputComponent->BindKey(EKeys::MotionController_Left_Thumbstick, IE_Pressed, this, &ABasePawn::OnL_STICK_Pressed);
		//TODO PlayerInputComponent->BindKey(EKeys::MotionController_Left_Thumbstick, IE_Released, this, &ABasePawn::OnL_STICK_Released);		

		//TODO touch events?
		//PlayerInputComponent->BindTouch(IE_Pressed, this, &ABasePawn::UpdateTouch(ETouchIndex::Type, FVector);

		//TODO axis events?
		//PlayerInputComponent->BindAxisKey(EKeys::MotionController_Left_Thumbstick_X, this, &ABasePawn::UpdateInput(float delta));
		
		
	}
}

ABasePawn* g_pBasePawn = NULL;
void ABasePawn::PreInit() {
	g_pBasePawn = this;

	// Initialize ABaseController variables
	m_pLHand = Cast<ABaseController>(m_pLChildActor->GetChildActor());
	m_pLHand->SetWhichHand(EControllerHand::Left);
	m_pLHand->SetStaticMesh(m_pLeftControllerMesh);

	m_pRHand = Cast<ABaseController>(m_pRChildActor->GetChildActor());
	m_pRHand->SetWhichHand(EControllerHand::Right);
	m_pRHand->SetStaticMesh(m_pRightControllerMesh);

	m_pRHand->m_rightControllerInput = m_rightControllerInput;
	m_pLHand->m_leftControllerInput = m_leftControllerInput;

	m_rightControllerInput = FEntityInputRegistrationParams();
	m_leftControllerInput = FEntityInputRegistrationParams();
}

//void ABasePawn::UpdateInput(float delta) {
	//Msg("Touch Input Test: %i", delta);
//}
