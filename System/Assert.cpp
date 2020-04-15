// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#include "Assert.h"
//#include "NLogger.h"

void _Assert(const char* function, const char* file, long line, bool bAssertion, const char* str) {
	if (!bAssertion) {

		// format debug information

		TArray<FStringFormatArg> dbgArgs;
		dbgArgs.Add(FStringFormatArg(function));
		dbgArgs.Add(FStringFormatArg(file));
		dbgArgs.Add(FStringFormatArg(line));
		FString debugInfo = FString::Format(TEXT("{0} in {1}({2})"), dbgArgs);

		// print information to message log

		FString message = FString(str);
		const auto Token = FTextToken::Create(FText::FromString(debugInfo));
		FMessageLog("PIE").Error(FText::FromString(FString::Printf(TEXT("( Assertion Error: %s ) -> "), *message)))->AddToken(Token);

		// quit game

		if (g_pWorld) {
			APlayerController* pPlayerController = g_pWorld->GetFirstPlayerController();
			if (pPlayerController) pPlayerController->ConsoleCommand("quit");
		}

	}
}
