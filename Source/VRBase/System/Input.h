#ifndef VRBASE_INPUT_H
#define VRBASE_INPUT_H

#include "GameFramework/Actor.h"
#include "System/predefs.h"
#include "System/EHandle.h"

abstract_class IBaseEntity;
class ABaseController;

extern ABaseController* g_pLeftController;
extern ABaseController* g_pRightController;

//Bitfields offset for button inputs
//These are used by the bitwise math in order to mark/unmark which
//buttons are being pressed.
#define IN_AX				BF(1)
#define IN_BY				BF(2)
#define IN_TRIGGER			BF(3)
#define IN_GRIP				BF(4)
#define IN_MENU				BF(5)

//Describes a specific setting of when a given entity is to be triggered
//by a controller
struct SEntityInputTriggerRequirement {
	EHANDLE m_ent; //Which entity is to be triggered by this event?
	uint32	m_iButton; //Bitfield - which button are we listening for?
	bool	m_bOnReleased; //Is this triggered when the button is released, instead of pressed?
};



#endif VRBASE_INPUT_H
