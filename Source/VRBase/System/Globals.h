// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#ifndef GLOBALS_H
#define GLOBALS_H

#include "CoreMinimal.h"
#include "predefs.h"
#include "time.h"
#include "NLogger.h"

extern UWorld* g_pWorld;

class CGlobalVars {
public:
	ftime curtime;
	ftime frametime;
	bool  ineditor = true; //if true, we are editing a world in the editor and are not playing it. For PIE, this is true


	void update();

	void reset();
	
	void checkReset();
	void markReset();
private:
	clock_t m_tPrevious;
	bool	m_bReset = true;
};

extern CGlobalVars* g_pGlobals;

#endif //GLOBALS_H