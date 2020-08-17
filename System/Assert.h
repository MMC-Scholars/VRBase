// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#ifndef ASSERT_H
#define ASSERT_H

#include "Globals.h"
#include "MessageLog.h"
#include "TokenizedMessage.h"

void _Assert(const char* function, const char* file, long line, bool bAssertion, const char* pszFormat, ...);
// implement pszFormat with const wchar_t* ?

#define Assert(bAssertion, pszFormat, ...) _Assert(__FUNCTION__, __FILE__, __LINE__, bAssertion, pszFormat, __VA_ARGS__)

#endif // ASSERT_H
