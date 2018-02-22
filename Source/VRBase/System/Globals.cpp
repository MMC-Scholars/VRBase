#include "CoreMinimal.h"
#include "Globals.h"

void CGlobalVars::update() {
	clock_t newclock = clock();
	ftime newtime = (newclock - m_tStart) / CLOCKS_PER_SEC;

	frametime = newtime - curtime;
	curtime = newtime;
}

void CGlobalVars::reset() {
	m_tStart = clock();
}

void CGlobalVars::checkReset() {
	if (m_bReset)
		reset();
}

void CGlobalVars::markReset() {
	m_bReset = true;
}