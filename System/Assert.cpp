// This software is under partial ownership by The Ohio State University, for it
// is a product of student employees. For official policy, see
// https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The
// Ohio State University's Office of Legal Affairs.

#include "Assert.h"

#define BUFFER_SIZE 512

void _Assert(const char *function, const char *file, long line, bool bAssertion,
             const char *pszFormat, ...) {
  if (!bAssertion) {
    va_list args;
    va_start(args, pszFormat);

    // convert variadic args to FString

    char buffer[BUFFER_SIZE];
    vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE - 1, pszFormat, args);
    FString message = buffer;

    // format debug information

    TArray<FStringFormatArg> dbgArgs;
    dbgArgs.Add(FStringFormatArg(function));
    dbgArgs.Add(FStringFormatArg(file));
    dbgArgs.Add(FStringFormatArg(line));
    FString debugInfo = FString::Format(TEXT("{0} in {1}({2})"), dbgArgs);

    // print information to message log

    //		FString message = FString(str);
    const auto Token = FTextToken::Create(FText::FromString(debugInfo));
    FMessageLog("PIE")
        .Error(FText::FromString(
            FString::Printf(TEXT("( Assertion Error: %s ) -> "), *message)))
        ->AddToken(Token);

    // quit game

    if (g_pWorld) {
      APlayerController *pPlayerController =
          g_pWorld->GetFirstPlayerController();
      if (pPlayerController)
        pPlayerController->ConsoleCommand("quit");
    }

    va_end(args);
  }
}
