// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#include "Assert.h"
#include "NLogger.h"

#define BUFFER_SIZE 512

void Assert(bool bAssertion, const char* pszFormat, ...) {
	if (!bAssertion) {
		va_list args;
		va_start(args, pszFormat);

		// convert variadic args to FString

		char buffer[BUFFER_SIZE];
		vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE - 1, pszFormat, args);
		FString str = buffer;

    
		Msg(str);

		va_end(args);
	}
}
