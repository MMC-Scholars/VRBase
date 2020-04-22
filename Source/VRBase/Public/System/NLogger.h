/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "System/predefs.h"

namespace NLogger {

	void VRBASE_API Message(const FString&);
	void VRBASE_API Message(const char* pszFormat, ...);
	void VRBASE_API Message(FColor c, ftime duration, const char* pszFormat, ...);

	void VRBASE_API Blurp(const FString&);
	void VRBASE_API Blurp(const char* pszFormat, ...);

	void VRBASE_API Warning(const FString&);
	void VRBASE_API Warning(const char* pszFormat, ...);

	void VRBASE_API Fatal(const FString&);
	void VRBASE_API Fatal(const char* pszFormat, ...);

}

inline VRBASE_API const wchar_t* WCStr(const FString& str) { return &(str[0]);}
VRBASE_API void Msg(const char* pszFormat, ...);
VRBASE_API void Msg(const wchar_t* pszFormat, ...);
inline VRBASE_API void Msg(const FString& str) { Msg(WCStr(str)); }

// shortcuts for Unreal structures

inline VRBASE_API void Msg(const AActor* actor) {
	Msg(actor->GetHumanReadableName());
}

inline VRBASE_API void Msg(const FVector& v) {
	Msg("FVector(%f,%f,%f)", v.X, v.Y, v.Z);
}

inline VRBASE_API void Msg(const FRotator& r) {
	Msg("FRotator(%f,%f,%f)", r.Roll, r.Pitch, r.Yaw);
}