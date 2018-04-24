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

inline const wchar_t* WCStr(const FString& str) { return &(str[0]);}
void Msg(const char* pszFormat, ...);
void Msg(const wchar_t* pszFormat, ...);