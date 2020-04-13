// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#include "Assert.h"
#include "NLogger.h"

void _Assert(const char* function, const char* file, long line, bool bAssertion, const char* str) {
	if (!bAssertion) {

		TArray<FStringFormatArg> dbgArgs;
		dbgArgs.Add(FStringFormatArg(function));
		dbgArgs.Add(FStringFormatArg(file));
		dbgArgs.Add(FStringFormatArg(line));
		FString debugMessage = FString::Format(TEXT("{0} in {1}({2})"), dbgArgs);

		FString message = FString(str);
		
		const auto Token = FTextToken::Create(FText::FromString(debugMessage));
		FMessageLog("PIE").Error(FText::FromString(FString::Printf(TEXT("( Assertion Error: %s ) -> "), *message)))->AddToken(Token);

		// quit game

		// this quits but closes editor too :/
		// FGenericPlatformMisc::RequestExit(false); 

		// this requires a UWorld* reference, only available from an actor
		// APlayerController* pPlayerController = GetWorld()->GetFirstPlayerController();
		// if (pPlayerController) pPlayerController->ConsoleCommand("quit");
	}
}
