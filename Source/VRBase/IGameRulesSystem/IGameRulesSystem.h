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
	}

	//Called before static initializers, and after all PreInit of IBaseEntity
	virtual void PreInit() {}

	//Called after all PostInit of IBaseEntity
	virtual void PostInit() {}

	//On any given tick, this will be called after the Think and DefaultThink of all IBaseEntity
	//And it will only be called if g_pGlobals->curtime > m_tNextThink
	//SetNextThinkTime must be called in this, or else Think() will stop
	virtual void Think() {}

	//Sets the next time this system to think
	void SetNextThinkTime(ftime t) {
		m_tNextThink = t;

		//Insertion sort - determine where we should be in the sorted list of IGameRulesSystem
		int32 index = 0;
		while (index < g_aGameRulesSystems.Num() && g_aGameRulesSystems[index]->m_tNextThink < m_tNextThink) index++;
		g_aGameRulesSystems.Insert(this, index);
	}

	ftime GetNextThinkTime(ftime t) {
		return m_tNextThink;
	}

private:
	ftime m_tNextThink;
};