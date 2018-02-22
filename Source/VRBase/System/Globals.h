// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#include "CoreMinimal.h"
#include "predefs.h"
#include "time.h"

class CGlobalVars {
public:
	ftime curtime;
	ftime frametime;


	void update();

	void reset();
	
	void checkReset();
	void markReset();
private:
	clock_t m_tStart;
	bool	m_bReset = true;
};

extern CGlobalVars* g_pGlobals;