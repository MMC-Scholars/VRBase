// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#ifndef ASSERT_H
#define ASSERT_H

#include "MessageLog.h"
#include "TokenizedMessage.h"

void Assert(bool bAssertion, const char* pszFormat, ...);
// TODO overload
//void Assert(bool bAssertion);

#endif // ASSERT_H
