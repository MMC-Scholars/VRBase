// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#include "Assert.h"
#include "NLogger.h"

void Assert(bool bResult, const char* pszFormat, ...) {
  if (!bResult) {
    va_list args;
	  va_start(args, pszFormat);
    
    Msg(pszFormat, args);

	  va_end(args);
  }
}

void Assert(bool bResult) {
  if (!bResult) {
    Assert(false, "");
  }
}