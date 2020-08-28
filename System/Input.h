/**
 * This software is under partial ownership by The Ohio State University,
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#ifndef VRBASE_INPUT_H
#define VRBASE_INPUT_H

#include "EHandle.h"
#include "GameFramework/Actor.h"
#include "predefs.h"

INTERFACE IBaseEntity;
class ABaseController;

extern ABaseController* g_pLeftController;
extern ABaseController* g_pRightController;
extern ABasePawn*       g_pBasePawn;

// Bitfields offset for button inputs.
// These are used by the bitwise math in order to
// mark/unmark which buttons are being pressed.
#define IN_AX      BF(1)
#define IN_BY      BF(2)
#define IN_TRIGGER BF(3)
#define IN_GRIP    BF(4)
#define IN_MENU    BF(5)
#define IN_STICK   BF(6)

// Describes a specific setting of when a given entity is to be triggered by a
// controller. These are generated by entities in order to register themeselves
// with controllers.
struct SEntityInputTriggerRequirement {
    EHANDLE m_ent;         // which entity is to be triggered by this event?
    uint32  m_iButton;     // bitfield - which button are we listening for?
    bool    m_bOnReleased; // is this triggered when the button is released, instead
                           // of pressed?
};

// forward declaration of entity input registration parameters
struct FEntityInputRegistrationParams;

#endif // VRBASE_INPUT_H