// Fill out your copyright notice in the Description page of Project Settings.

#include "ABaseMoving.h"

ABaseMoving::ABaseMoving() {
	m_lInitialLerp = 0;
	m_flLerpSpeed = 10;
}

void ABaseMoving::PreInit() {
	SetLerpPosition(m_lInitialLerp);
}

void ABaseMoving::PostInit() {

}

void ABaseMoving::Open() {
	if (IsOpen()) {
		return;
	}

	//SetThink((BASEPTR)&ABaseMoving::OpenThink);
}

void ABaseMoving::Close() {

}

bool ABaseMoving::IsOpen() const {
	return (FMath::IsNearlyEqual(m_lCurrentLerp, 1.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(1.0f, m_lCurrentLerp, OPENCLOSE_MEASURE_TOLERANCE)));
}

bool ABaseMoving::IsClosed() const {
	return (FMath::IsNearlyEqual(m_lCurrentLerp, 0.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(0.0f, m_lCurrentLerp, OPENCLOSE_MEASURE_TOLERANCE)));
}

bool ABaseMoving::IsOpening() const {
	return false;
}

bool ABaseMoving::IsClosing() const {
	return false;
}

void ABaseMoving::OpenThink(){

}

void ABaseMoving::CloseThink() {

}