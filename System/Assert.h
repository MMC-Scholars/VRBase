#ifndef ASSERT_H
#define ASSERT_H

#include "Globals.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"

void _Assert(const char* function, const char* file, long line, bool bAssertion,
             const char* pszFormat, ...);
// implement pszFormat with const wchar_t* ?

#define Assert(bAssertion, pszFormat, ...)                                          \
    _Assert(__FUNCTION__, __FILE__, __LINE__, bAssertion, pszFormat, __VA_ARGS__)

#endif // ASSERT_H
