// Fill out your copyright notice in the Description page of Project Settings.

#include "ABasePawn.h"


ABasePawn::ABasePawn() {
	Tags.Add(TAG_BASEPAWN);
	m_pSelfAsActor = this;

	// disable event tick
	bAllowTickBeforeBeginPlay = false;
	SetActorTickEnabled(false);

	// Capsule Root Component
	m_pRootCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	m_pRootCapsule->InitCapsuleSize(16.0, 96.0);
	//m_pRootCapsule->InitCapsuleSize(16.0, 112.0);
	RootComponent = m_pRootCapsule;

	// Player Root Scene Component
	m_pPlayerRoot = CreateDefaultSubobject<USceneComponent>("Player Root");
	m_pPlayerRoot->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// HMD Camera
	m_pCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_pCamera->bLockToHmd = true;
	m_pCamera->AttachToComponent(m_pPlayerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//? setting hmd height doesn't work correctly yet...
	FQuat DeviceQuat;
	FVector DevicePosition;
	GEngine->HMDDevice->GetCurrentOrientationAndPosition(DeviceQuat, DevicePosition);
	
	m_pCamera->SetWorldLocation(DevicePosition);


	
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	// Capsule Root Component
	/*UCapsuleComponent *Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->InitCapsuleSize(16.0, 112.0);
	RootComponent = Capsule;

	// Player Root Scene Component
	m_pPlayerRoot = CreateDefaultSubobject<USceneComponent>("Player Root");
	m_pPlayerRoot->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	m_pPlayerRoot->AddLocalOffset(FVector(0, 0, -83));
	USceneComponent *attachRoot = m_pPlayerRoot;

	// HMD Camera
	m_pCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_pCamera->bLockToHmd = true;

	m_pCamera->AttachToComponent(attachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	auto pSetupController = [&](UMotionControllerComponent** component, UChildActorComponent** childActor, AHand** assigned, EControllerHand h, const char* pszName) {
		*component = CreateDefaultSubobject<UMotionControllerComponent>(pszName);
		(*component)->AttachToComponent(attachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		(*component)->Hand = h;

		*childActor = CreateDefaultSubobject<UChildActorComponent>(pszName);
		(*childActor)->AttachToComponent(m_pLeftMotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		(*childActor)->SetChildActorClass(AHand::StaticClass());
		(*childActor)->CreateChildActor();

		*assigned = Cast<AHand>((*childActor)->GetChildActor());
	};

	pSetupController(&m_pLeftMotionController, &m_pLeftChildActor, &m_pLHand, EControllerHand::Left, "Left");
	pSetupController(&m_pRightMotionController, &m_pRightChildActor, &m_pRHand, EControllerHand::Right, "Right");*/

	
	
	
	// L Motion Controller
	//UMotionControllerComponent* m_ptest = CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
	/*m_pLMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
	m_pLMotionController->Hand = EControllerHand::Left;
	m_pLMotionController->AttachToComponent(attachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	//m_pLChildActor = CreateDefaultSubobject<UChildActorComponent>("Left Child Actor");
	//m_pLChildActor->SetChildActorClass(AHand::StaticClass());
	//m_pLChildActor->AttachToComponent(m_pLMotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// R Motion Controller
	m_pRMotionController = CreateDefaultSubobject<UMotionControllerComponent>("Right Motion Controller");
	m_pRMotionController->Hand = EControllerHand::Right;
	m_pRMotionController->AttachToComponent(attachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//m_pRChildActor = CreateDefaultSubobject<UChildActorComponent>("Right Child Actor");
	//m_pRChildActor->SetChildActorClass(AHand::StaticClass());
	//m_pRChildActor->AttachToComponent(m_pRMotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	*/
}

