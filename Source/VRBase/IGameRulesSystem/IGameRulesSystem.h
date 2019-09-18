/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "UnrealEngine.h"
#include "System/system.h"

class IGameRulesSystem;
extern TArray<IGameRulesSystem*> g_aGameRulesSystems;

class IGameRulesSystem {
	public:

	//Called on DLL load
	IGameRulesSystem() {
		SetNextThinkTime(-FLT_MAX);
		g_aGameRulesSystems.Add(this);
	}

	//Called before static initializers, and after all PreInit of IBaseEntity
	virtual void PreInit() {}

	//Called after all PostInit of IBaseEntity
	virtual void PostInit() {}

	//On any given tick, this will be called after the Think and DefaultThink of all IBaseEntity
	//And it will only be called if g_pGlobals->curtime > m_tNextThink
	virtual void Think() {}

	//Sets the next time this system to think
	void SetNextThinkTime(ftime t) { m_tNextThink = t; }

	ftime GetNextThinkTime() { return m_tNextThink; }

	private:
		ftime m_tNextThink;
};