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
inline void Msg(const FString& str) { Msg(WCStr(str)); }

// shortcuts for Unreal structures

inline void Msg(const AActor* actor) {
	Msg(actor->GetHumanReadableName());
}

inline void Msg(const FVector& v) {
	Msg("FVector(%f,%f,%f)", v.X, v.Y, v.Z);
}

inline void Msg(const FRotator& r) {
	Msg("FRotator(%f,%f,%f)", r.Roll, r.Pitch, r.Yaw);
}