

#include "ABasePawn.h"

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

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);



	if (PlayerInputComponent) {
		PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &UpdateInput);
		//float BValue = PlayerInputComponent->GetKeyValue(EKeys::B);
		//Msg(PlayerInputComponent->KeyBindings);
	}



	//check(InputComponent);

	//InputComponent->BindAction("EventLTrigger", IE_Pressed, this, &ABasePawn::UpdateInput);

	// Event L Trigger
	//InputComponent->BindAction("EventLTrigger", IE_Pressed, this, &AFPChar::OnPressLTrigger);
	//InputComponent->BindAction("EventLTrigger", IE_Released, this, &AFPChar::OnReleaseLTrigger);
	// Event L Trackpad
	//InputComponent->BindAction("EventLTrackpad", IE_Pressed, this, &AFPChar::OnPressLTrackpad);
	//InputComponent->BindAction("EventLTrackpad", IE_Released, this, &AFPChar::OnReleaseLTrackpad);

	// Event R Trigger
	//InputComponent->BindAction("EventRTrigger", IE_Pressed, this, &AFPChar::OnPressRTrigger);
	//InputComponent->BindAction("EventRTrigger", IE_Released, this, &AFPChar::OnReleaseRTrigger);
	// Event R Trackpad
	//InputComponent->BindAction("EventRTrackpad", IE_Pressed, this, &AFPChar::OnPressRTrackpad);
	//InputComponent->BindAction("EventRTrackpad", IE_Released, this, &AFPChar::OnReleaseRTrackpad);



}


void ABasePawn::PreInit() {

	// Initialize ABaseController variables
	m_pLHand = Cast<ABaseController>(m_pLChildActor->GetChildActor());
	m_pLHand->setWhichHand(EControllerHand::Left);

	m_pRHand = Cast<ABaseController>(m_pRChildActor->GetChildActor());
	m_pRHand->setWhichHand(EControllerHand::Right);

}



void ABasePawn::UpdateInput() {
	Msg("pressed.");
}

