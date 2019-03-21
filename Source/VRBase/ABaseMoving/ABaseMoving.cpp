
#include "ABaseController\ABaseController.h"
#include "ABaseMoving.h"

ABaseMoving::ABaseMoving() {
	m_lInitialLerp = 0;
	m_flLerpSpeed = 10;
	m_binAttachThink = false;
}

void ABaseMoving::PreInit() {
	SetLerpPosition(m_lInitialLerp);
}

void ABaseMoving::PostInit() {

}

void ABaseMoving::OnUsed(ABaseEntity*) {
	if (!m_binAttachThink) {
		SetThink(&ABaseMoving::AttachThink);
		m_binAttachThink = true;
	}
	else {
		StopThink();
		m_binAttachThink = false;
	}
}

void ABaseMoving::SetPositionFromController(ABaseController* pController) {

}

void ABaseMoving::Open() {
	if (IsOpen()) {
		return;
	}

	SetThink(&ABaseMoving::OpenThink);
}

void ABaseMoving::Close() {
	SetThink(&ABaseMoving::CloseThink);
}

bool ABaseMoving::IsOpen() const {
	return m_lCurrentLerp >= 1.f; /*(FMath::IsNearlyEqual(m_lCurrentLerp, 1.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(1.0f, m_lCurrentLerp, OPENCLOSE_MEASURE_TOLERANCE)));*/
}

bool ABaseMoving::IsClosed() const {
	return m_lCurrentLerp <= 0.f; /*(FMath::IsNearlyEqual(m_lCurrentLerp, 0.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(0.0f, m_lCurrentLerp, OPENCLOSE_MEASURE_TOLERANCE)));*/
}

bool ABaseMoving::IsOpening() const {
	return false;
}

bool ABaseMoving::IsClosing() const {
	return false;
}

void ABaseMoving::OpenThink(void* vpBaseMoving){
	ABaseMoving* pMoving = ExtractArg<ABaseMoving>(vpBaseMoving);

	//If we've finished opening, stop opening
	if (pMoving->IsOpen()) {
		pMoving->OnFinishOpen();
		pMoving->StopThink();
	}
	//Otherwise, follow the lerp speed
	else {
		//Calculate next lerp position based on speed and time
		//Also notify our child class that our position has changed, such that it can do the actual movement
		pMoving->SetLerpPosition(pMoving->m_lCurrentLerp + pMoving->m_flLerpSpeed * g_pGlobals->frametime);
	}
}

void ABaseMoving::CloseThink(void* vpBaseMoving) {
	ABaseMoving* pMoving = ExtractArg<ABaseMoving>(vpBaseMoving);

	//If we've finished closing, stop closing
	if (pMoving->IsClosed()) {
		pMoving->OnFinishClose();
		pMoving->StopThink();
	}
	//Otherwise, follow the lerp speed
	else {
		//Calculate next lerp position based on speed and time
		//Also notify our child class that our position has changed, such that it can do the actual movement
		pMoving->SetLerpPosition(pMoving->m_lCurrentLerp - pMoving->m_flLerpSpeed * g_pGlobals->frametime);
	}
}

void ABaseMoving::AttachThink(void* vpBaseMoving) {
	static int frameCount = 0;
	frameCount++;
	if (frameCount == 100) {
		frameCount = 0;
		Msg(__FUNCTION__);
	}
	ABaseMoving* pMoving = ExtractArg<ABaseMoving>(vpBaseMoving);
	pMoving->SetPositionFromController(pMoving->m_pHoldingController);
}