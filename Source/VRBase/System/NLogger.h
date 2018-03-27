#pragma once

#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "predefs.h"

namespace NLogger {

			void Message(const FString&);
			void Message(const char* pszFormat, ...);
			void Message(FColor c, ftime duration, const char* pszFormat, ...);

			void Blurp(const FString&);
			void Blurp(const char* pszFormat, ...);

			void Warning(const FString&);
			void Warning(const char* pszFormat, ...);

			void Fatal(const FString&);
			void Fatal(const char* pszFormat, ...);

}

void Msg(const char* pszFormat, ...);