// Fill out your copyright notice in the Description page of Project Settings.

#include "AMoveRotational.h"
#include "System/NLogger.h"

AMoveRotational::AMoveRotational() {
	m_pAxis = CreateDefaultSubobject<USplineComponent>("spline axis");
	RootComponent = m_pAxis;
	m_pPickupMeshComponent->SetupAttachment(RootComponent);

	m_fRotRadius = 50;
	m_fRotRange = 360;
}

void AMoveRotational::OnConstruction(const FTransform& transform) {
	Super::OnConstruction(transform);

	// set mesh initial lerp
	m_vRotAxis = m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local) - m_pAxis->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	m_vInitialDirection = m_fRotRadius * (m_pAxis->GetRightVectorAtSplinePoint(0, ESplineCoordinateSpace::World) ^ m_vRotAxis);
	m_vTempAttachLoc = m_vInitialDirection.RotateAngleAxis(m_lInitialLerp * m_fRotRange, m_vRotAxis / m_vRotAxis.Size());
	
	m_vRangeVector = m_vInitialDirection.RotateAngleAxis(m_fRotRange, m_vRotAxis / m_vRotAxis.Size());
	
	// transform mesh into correct initial position
	FVector vNewAxisLoc = 0.5 * m_vRotAxis + m_fRotRadius * (m_vTempAttachLoc / m_vTempAttachLoc.Size());
	FRotator rNewAxisRot = FRotator(m_vRotAxis.Rotation().Pitch - 90, m_vRotAxis.Rotation().Yaw, m_vRotAxis.Rotation().Roll);
	m_pPickupMeshComponent->SetRelativeLocationAndRotation(vNewAxisLoc, rNewAxisRot);

	SetPositionFromController(NULL);
}

void AMoveRotational::SetPositionFromController(ABaseController* pController) {
	FVector vControllerDir = FVector::PointPlaneProject(m_vTempAttachLoc, m_vInitialDirection, m_vRotAxis);
	m_lCurrentLerp = FMath::Acos( (vControllerDir | m_vInitialDirection) / (m_vInitialDirection.Size() * vControllerDir.Size()) ) / abs(m_fRotRange);

	if (abs(m_lCurrentLerp) <= 1) {
		FRotator rLerpRotation = FMath::Lerp(m_vInitialDirection.Rotation(), m_vRangeVector.Rotation(), m_lCurrentLerp) - m_vInitialDirection.Rotation();
		// FVector vLerpDirection = m_vInitialDirection.RotateAngleAxis(fRotAngle, m_vRotAxis / m_vRotAxis.Size());
		// FRotator rLerpRotation = (FVector::Parallel(vLerpDirection, vControllerDir)) ? (vLerpDirection.Rotation()) : (FRotator(180) - vLerpDirection.Rotation());

		// FRotator rLerpRotation = vControllerDir.Rotation();

		m_pAxis->SetWorldRotation( rLerpRotation + FRotator(90, 0, 0) );
	}
	
	Msg("Point 1: ");
	Msg(m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));
}

void AMoveRotational::SetLerpPosition(float _lerp) {
	Super::SetLerpPosition(_lerp);
}

void AMoveRotational::DefaultThink() {
	Super::DefaultThink();
}
