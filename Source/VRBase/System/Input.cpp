#include "Input.h"
#include "IBaseEntity/IBaseEntity.h"

void CEntityInput::Init(
	IBaseEntity* pForEnt,
	void(*pFunc)(const SEntityInputEvent* pEnt)) {

	m_pEnt = pForEnt;
	m_pFunc = pFunc;
}

void CEntityInput::Activate(CBaseController* pActivator) {
	SEntityInputEvent e = { m_pEnt.Get(), pActivator };
	m_pFunc(&e);
}

void CEntityInput::AddButtons(uint32 buttons, bool bOnRelease, bool bTouch) {
	uint32* pAffected = GetButtons(bOnRelease, bTouch);

	*pAffected |= buttons;
}

uint32* CEntityInput::GetButtons(bool bOnRelease, bool bTouch) {
	uint32* pb = &m_iPressed;
	if (bOnRelease) {
		if (bTouch)
			pb = &m_iTouchedReleased;
		else
			pb = &m_iReleased;
	}
	else if (bTouch)
		pb = &m_iTouched;
	return pb;
}

CBaseController* g_pLeftController = nullptr;
CBaseController* g_pRightController = nullptr;