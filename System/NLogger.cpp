#include "NLogger.h"

namespace NLogger {
#define BUFFER_SIZE 512

//-------------------------------------------------------------------------------------
// Implementation functions
//-------------------------------------------------------------------------------------

char        buffer[BUFFER_SIZE];
static void VMsgMaster(FColor c, ftime duration, const char* pszFormat,
                       va_list args) {
    if (GEngine) {
        vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE - 1, pszFormat, args);
        FString str = buffer;
        GEngine->AddOnScreenDebugMessage(-1, duration, c, str);
    }
}

wchar_t     wbuffer[BUFFER_SIZE];
static void VWMsgMaster(FColor c, ftime duration, const wchar_t* pszFormat,
                        va_list args) {
    if (GEngine) {
        vswprintf_s(wbuffer, BUFFER_SIZE, pszFormat, args);
        FString str = wbuffer;
        GEngine->AddOnScreenDebugMessage(-1, duration, c, str);
    }
}

inline void MsgMaster(FColor c, ftime duration, const FString& str) {
    if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, c, str); }
}

//-------------------------------------------------------------------------------------
// Public interface
//-------------------------------------------------------------------------------------

void Message(const FString& str) { MsgMaster(FColor::Cyan, 15.0f, str); }
void Message(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    VMsgMaster(FColor::Cyan, 5.0f, pszFormat, args);
    va_end(args);
}
void Message(FColor c, ftime duration, const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    VMsgMaster(c, duration, pszFormat, args);
    va_end(args);
}

void Blurp(const FString& str) { MsgMaster(FColor::Cyan, 0.2f, str); }
void Blurp(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    VMsgMaster(FColor::Cyan, 0.3f, pszFormat, args);
    va_end(args);
}

void Warning(const FString& str) { MsgMaster(FColor::Yellow, 5.0f, str); }
void Warning(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    VMsgMaster(FColor::Yellow, 5.0f, pszFormat, args);
    va_end(args);
}

void Fatal(const FString& str) { MsgMaster(FColor::Red, 5.0f, str); }
void Fatal(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    VMsgMaster(FColor::Red, 5.0f, pszFormat, args);
    va_end(args);
}
} // namespace NLogger

void Msg(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    NLogger::VMsgMaster(FColor::Cyan, 10.0f, pszFormat, args);
    va_end(args);
}
void Msg(const wchar_t* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    NLogger::VWMsgMaster(FColor::Cyan, 10.0f, pszFormat, args);
    va_end(args);
}