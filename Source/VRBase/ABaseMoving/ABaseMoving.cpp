#include "ABaseMoving.h"
#include "ABaseController/ABaseController.h"

ABaseMoving::ABaseMoving() {
	m_lInitialLerp = 0;
	m_flLerpSpeed = 10;
	m_bInAttachThink = false;
	m_pHoldingController = NULL;
}

void ABaseMoving::PreInit() {
	Super::PreInit();
	SetLerpPosition(m_lInitialLerp);
}

void ABaseMoving::OnUsed(ABaseEntity* pActivator) {
	Msg(__FUNCTION__);
	ABaseController* pController = dynamic_cast<ABaseController*>(pActivator);
	if (pController) {

		if (!m_bInAttachThink) {
			m_pHoldingController = pController;
			SetThink(&ABaseMoving::AttachThink);
			m_bInAttachThink = true;
		}
		else if (pController == m_pHoldingController){
			m_pHoldingController = NULL;
			StopThink();
			m_bInAttachThink = false;
		}
	}
}

bool ABaseMoving::IsUseableBy(const ABaseController* pController) const {
	if (pController->m_iButtonsReleased && !m_pHoldingController)
		return false;
	return Super::IsUseableBy(pController);
}

void ABaseMoving::SetPositionFromController(ABaseController* pController) {
	Msg(__FUNCTION__);
}

void ABaseMoving::Open() {
	if (IsOpen())
		return;

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

	// if finished opening, stop opening
	if (pMoving->IsOpen()) {
		pMoving->OnFinishOpen();
		pMoving->StopThink();
	}
	// otherwise, follow the lerp speed
	else {
		// calculate next lerp position based on speed and time
		// also notify our child class that our position has changed, such that it can do the actual movement
		pMoving->SetLerpPosition(pMoving->m_lCurrentLerp + pMoving->m_flLerpSpeed * g_pGlobals->frametime);
	}
}

void ABaseMoving::CloseThink(void* vpBaseMoving) {
	ABaseMoving* pMoving = ExtractArg<ABaseMoving>(vpBaseMoving);

	// if finished closing, stop closing
	if (pMoving->IsClosed()) {
		pMoving->OnFinishClose();
		pMoving->StopThink();
	}
	// otherwise, follow the lerp speed
	else {
		// calculate next lerp position based on speed and time
		// also notify our child class that our position has changed, such that it can do the actual movement
		pMoving->SetLerpPosition(pMoving->m_lCurrentLerp - pMoving->m_flLerpSpeed * g_pGlobals->frametime);
	}
}

void ABaseMoving::AttachThink(void* vpBaseMoving) {
	ABaseMoving* pMoving = ExtractArg<ABaseMoving>(vpBaseMoving);
	if (!pMoving->IsUseableBy(pMoving->m_pHoldingController)) {
		pMoving->StopThink();
	}

	pMoving->SetPositionFromController(pMoving->m_pHoldingController);
}