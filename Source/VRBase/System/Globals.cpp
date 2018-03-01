#include "Globals.h"
#include "CoreMinimal.h"

static CGlobalVars g_vars;
CGlobalVars* g_pGlobals = &g_vars;

void CGlobalVars::update() {
	clock_t newclock = clock();
	frametime = (newclock - m_tPrevious) / CLOCKS_PER_SEC;
	m_tPrevious = newclock;

	curtime = curtime + frametime;
}

void CGlobalVars::reset() {
	curtime = -99999.99f; //lowest value with 2 decimal digits, appoximmately
}

void CGlobalVars::checkReset() {
	if (m_bReset)
		reset();
}

void CGlobalVars::markReset() {
	m_bReset = true;
}