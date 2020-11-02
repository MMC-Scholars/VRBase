#include "Debug.h"

DEFINE_LOG_CATEGORY_STATIC(VRBase, Log, Log)

ADebug::ADebug() { PrimaryActorTick.bCanEverTick = false; }

FString ADebug::pszFormatToFString(const char* pszFormat, va_list args) {
    char buffer[m_iBufferSize];
    vsnprintf_s(buffer, m_iBufferSize, pszFormat, args);
    return FString(buffer);
}

void ADebug::Log(FString message, FLinearColor color, float duration) {
    // log to screen
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, duration, color.Quantize(), message);
    }
    // log to output log
    UE_LOG(VRBase, Log, TEXT("%s"), *message);
}

void ADebug::Log(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);

    Log(pszFormatToFString(pszFormat, args));

    va_end(args);
}