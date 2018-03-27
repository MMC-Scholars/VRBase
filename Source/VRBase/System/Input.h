#ifndef VRBASE_INPUT_H
#define VRBASE_INPUT_H

#include "GameFramework/Actor.h"
#include "System/predefs.h"
#include "System/EHandle.h"

#define BF(i) (1 << (i))
#define IN_A				BF(1)
#define IN_B				BF(2)
#define IN_TRIGGER			BF(3)
#define IN_GRIP				BF(4)
#define IN_MENU				BF(5)


abstract_class IBaseEntity;
class CBaseController;

struct SEntityInputEvent final {
	IBaseEntity*		m_ent; //what entity actually registered for this input?
	CBaseController*	m_activator; //which controller triggered this input?
};

//--------------------------------------------------------
// 
//--------------------------------------------------------
class CEntityInput final {
public:

	void Init(
		IBaseEntity* pForEnt, 
		void(*pFunc)(const SEntityInputEvent* pEnt)
	);
	bool IsValid() const {
		return m_pEnt && m_pFunc;
	}
	void Activate(CBaseController* pActivator);
	
	void AddButtons(uint32 buttons, bool bOnRelease = false, bool bTouch = false);
	uint32* GetButtons(bool bOnRelease = false, bool bTouch = false);
private:
	EHANDLE m_pEnt;
	void (*m_pFunc)(const SEntityInputEvent* pEnt) = nullptr;
	char m_flags;

	uint32 m_iPressed;
	uint32 m_iReleased;
	uint32 m_iTouched;
	uint32 m_iTouchedReleased;
};


extern CBaseController* g_pLeftController;
extern CBaseController* g_pRightController;
inline bool ControllersReady() {
	return g_pRightController && g_pLeftController;
}

#endif VRBASE_INPUT_H
