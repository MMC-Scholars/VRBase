/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "CoreMinimal.h"
#include "predefs.h"
#include <ctime>
#include "NLogger.h"

extern UWorld* g_pWorld;

class CGlobalVars {
	public:
		ftime curtime;
		ftime frametime;
		bool  ineditor = true; 				// true if in Unreal editor or in Play In Editor
		bool  worldcreated = false; 	// true if the world has already been created and BeginPlays have started.

		void update();
		void reset();
		void checkReset();
		void markReset();

	private:
		clock_t m_tPrevious;
		bool	m_bReset = true;
};

extern CGlobalVars* g_pGlobals;

inline bool IsCookedBuild() {
	return !WITH_EDITOR;
}

#endif // GLOBALS_H