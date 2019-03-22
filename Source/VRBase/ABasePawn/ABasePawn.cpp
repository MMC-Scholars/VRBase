

#include "ABasePawn.h"
#include "System/NLogger.h"

#define DEFAULT_CONTROLLER_CLASS ABaseController
#define CAPSULE_HEIGHT 96.0

ABasePawn::ABasePawn() {
	Tags.Add(TAG_BASEPAWN);
	m_pSelfAsActor = this;
	m_pTeleportBounds = NULL;

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
	m_pCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_pCamera->bLockToHmd = true;
	m_pCamera->SetupAttachment(m_pPlayerRoot);

	// L Motion Controller
	m_pLMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
	m_pLMotionController->Hand = EControllerHand::Left;
	m_pLMotionController->SetupAttachment(m_pPlayerRoot);


	// L Child Actor
	m_pLChildActor = CreateDefaultSubobject<UChildActorComponent>("Left Child Actor");
	m_pLChildActor->SetChildActorClass(DEFAULT_CONTROLLER_CLASS::StaticClass());
	m_pLChildActor->SetupAttachment(m_pLMotionController);

	// R Motion Controller
	m_pRMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Right Motion Controller");
	m_pRMotionController->Hand = EControllerHand::Right;
	m_pRMotionController->SetupAttachment(m_pPlayerRoot);

	// R Child Actor
	m_pRChildActor = CreateDefaultSubobject<UChildActorComponent>("Right Child Actor");
	m_pRChildActor->SetChildActorClass(DEFAULT_CONTROLLER_CLASS::StaticClass());
	m_pRChildActor->SetupAttachment(m_pRMotionController);

	// automatically possess pawn placed in world instead of generating a pawn
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
		//PlayerInputComponent->BindAxisKey(EKeys::MotionController_Left_Thumbstick_X, this, &ABasePawn::UpdateInput);
		
		
	}
}

ABasePawn* g_pBasePawn = NULL;
void ABasePawn::PreInit() {
	g_pBasePawn = this;

	//Set tracking origin to floor
	auto HMD = GEngine->HMDDevice.Get();
	HMD->SetTrackingOrigin(EHMDTrackingOrigin::Floor);

	FVector loc = GetActorLocation();
	SetActorLocation(FVector(loc.X, loc.Y, loc.Z - CAPSULE_HEIGHT));

	SetControllerClass(m_pLControllerClass, m_pRControllerClass);

	m_rightControllerInput = FEntityInputRegistrationParams();
	m_leftControllerInput = FEntityInputRegistrationParams();
}

void ABasePawn::SetControllerClass(UClass* LControllerClass, UClass* RControllerClass) {

	// if not null
	if (LControllerClass && RControllerClass) {

		// set child actors
		m_pLChildActor->SetChildActorClass(LControllerClass);
		m_pRChildActor->SetChildActorClass(RControllerClass);

		// cast to ABaseController
		m_pLHand = Cast<DEFAULT_CONTROLLER_CLASS>(m_pLChildActor->GetChildActor());
		if (m_pLHand) {
			m_pLHand->SetWhichHand(EControllerHand::Left);
			m_pLHand->SetStaticMesh(m_pLeftControllerMesh);
			m_pLHand->m_pOwnerPawn = this;
		}

		// cast to ABaseController
		m_pRHand = Cast<DEFAULT_CONTROLLER_CLASS>(m_pRChildActor->GetChildActor());
		if (m_pRHand) {
			m_pRHand->SetWhichHand(EControllerHand::Right);
			m_pRHand->SetStaticMesh(m_pRightControllerMesh);
			m_pRHand->m_pOwnerPawn = this;
		}
		if (m_pLHand && m_pRHand) {
			m_pLHand->m_leftControllerInput = m_leftControllerInput;
			m_pRHand->m_rightControllerInput = m_rightControllerInput;
		}
	}

}

bool ABasePawn::CanTeleportToLocation(const FVector& loc) {
	//If we don't have a bounds, return true
	// This will help unexperienced VR developers avoid problems
	if (!m_pTeleportBounds)
		return true;

	//Check if the given location is within our bounds
	FVector boxOrigin, boxExtent;
	m_pTeleportBounds->GetActorBounds(false, boxOrigin, boxExtent);

	// This is the logic IsInsideOrOn() should compute 
	// but for some reason it returns a different answer than
	// expected. This will have to do :')
	return (
		loc.X >= boxOrigin.X - boxExtent.X && loc.X <= boxOrigin.X + boxExtent.X &&
		loc.Y >= boxOrigin.Y - boxExtent.Y && loc.Y <= boxOrigin.Y + boxExtent.Y &&
		loc.Z >= boxOrigin.Z - boxExtent.Z && loc.Z <= boxOrigin.Z + boxExtent.Z
	);
}

bool ABasePawn::TeleportPlayer(const FVector& loc) {
	//First check if it is legal to enter this location
	if (!CanTeleportToLocation(loc))
		return false;

	//Teleport with the offset
	SetActorLocation(loc);
	return true;
}