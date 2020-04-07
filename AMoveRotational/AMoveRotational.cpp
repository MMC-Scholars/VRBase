// Fill out your copyright notice in the Description page of Project Settings.

#include "AMoveRotational.h"
#include "System/NLogger.h"

AMoveRotational::AMoveRotational() {
	m_pAxis = CreateDefaultSubobject<USplineComponent>("spline axis");
	RootComponent = m_pAxis;
	m_pPickupMeshComponent->SetupAttachment(RootComponent);

	m_fRotRadius = 50;
	m_fRotRange = 360;

	m_vRotAxis = m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local) - m_pAxis->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	m_vInitialDirection = m_fRotRadius * (m_pAxis->GetRightVectorAtSplinePoint(0, ESplineCoordinateSpace::World) ^ m_vRotAxis);
}

void AMoveRotational::OnConstruction(const FTransform& transform) {
	Super::OnConstruction(transform);

	// set mesh initial lerp
	// m_vRotAxis = m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local) - m_pAxis->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	// m_vInitialDirection = m_fRotRadius * (m_pAxis->GetRightVectorAtSplinePoint(0, ESplineCoordinateSpace::World) ^ m_vRotAxis);
	m_vTempAttachLoc = m_vInitialDirection.RotateAngleAxis(m_lInitialLerp * m_fRotRange, m_vRotAxis / m_vRotAxis.Size());
	
	m_vRangeVector = m_vInitialDirection.RotateAngleAxis(m_fRotRange, m_vRotAxis / m_vRotAxis.Size());
	
	// transform mesh into correct initial position
	FVector vNewAxisLoc = 0.5 * m_vRotAxis + m_fRotRadius * (m_vInitialDirection / m_vInitialDirection.Size());
	FRotator rNewAxisRot = FRotator(m_vRotAxis.Rotation().Pitch - 90, m_vRotAxis.Rotation().Yaw, m_vRotAxis.Rotation().Roll);
	m_pPickupMeshComponent->SetRelativeLocationAndRotation(vNewAxisLoc, rNewAxisRot);
	// FRotator rNewAxisRot = FRotator(m_vTempAttachLoc.Rotation().Pitch, m_vTempAttachLoc.Rotation().Yaw, m_vTempAttachLoc.Rotation().Roll);
	// FRotator rNewAxisRot = (m_vTempAttachLoc - m_pAxis->GetLocationAtDistanceAlongSpline(m_vRotAxis.Size() / 2, ESplineCoordinateSpace::World)).Rotation();
	// m_pPickupMeshComponent->SetRelativeLocation(vNewAxisLoc);
	// m_pPickupMeshComponent->SetWorldRotation(rNewAxisRot);

	SetPositionFromController(NULL);
}

void AMoveRotational::SetPositionFromController(ABaseController* pController) {
	FVector vControllerDir = FVector::PointPlaneProject(m_vTempAttachLoc, m_vInitialDirection, m_vRotAxis);
	float fSmallAngle = FMath::Acos( (vControllerDir | m_vInitialDirection) / (m_vInitialDirection.Size() * vControllerDir.Size()) ) * 180 / PI;
	
	FVector vRotated = m_vInitialDirection.RotateAngleAxis(fSmallAngle, m_vRotAxis);
	float fRotAngle = (vControllerDir / vControllerDir.Size()).Equals(vRotated / vRotated.Size(), 1) ? (fSmallAngle) : (360 - fSmallAngle);

	m_lCurrentLerp = fRotAngle / abs(m_fRotRange);

	if (m_lCurrentLerp <= 1) {
		// FRotator rLerpRotation = FMath::Lerp(m_vInitialDirection.Rotation(), m_vRangeVector.Rotation(), m_lCurrentLerp);
		fSmallAngle = (fRotAngle > 180) ? (-fSmallAngle) : (fSmallAngle);
 		FRotator rWrongAxis = m_vInitialDirection.RotateAngleAxis(fSmallAngle, m_vRotAxis / m_vRotAxis.Size()).Rotation();
		FRotator rLerpRotation = FRotator(0, rWrongAxis.Yaw, rWrongAxis.Pitch);
		// FRotator rLerpRotation = (FVector::Parallel(vLerpDirection, vControllerDir)) ? (vLerpDirection.Rotation()) : (FRotator(180) - vLerpDirection.Rotation());

		// FRotator rLerpRotation = vControllerDir.Rotation();

		m_pAxis->SetWorldRotation( m_vInitialDirection.Rotation() );
		Msg("%f", fRotAngle);
	}
	
	//Msg("Point 1: ");
	//Msg(m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));
	//float vRotAxisMag = (m_pAxis->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World) - m_pAxis->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World)).Size();
	//if ( (vControllerDir / vControllerDir.Size()).Equals(rotated / rotated.Size(), 1) )
	//Msg(m_vTempAttachLoc - m_pAxis->GetLocationAtDistanceAlongSpline(vRotAxisMag / 2, ESplineCoordinateSpace::World));
}

void AMoveRotational::SetLerpPosition(float _lerp) {
	Super::SetLerpPosition(_lerp);
}

void AMoveRotational::DefaultThink() {
	Super::DefaultThink();
}
