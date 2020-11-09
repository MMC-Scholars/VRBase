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

void ADebug::LogWarning(FString message, FLinearColor color, float duration) {
    Log(message, color.Quantize(), duration);
}

void ADebug::LogWarning(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    LogWarning(pszFormatToFString(pszFormat, args));
    va_end(args);
}

void ADebug::LogError(FString message, FLinearColor color, float duration) {
    Log(message, color.Quantize(), duration);
}

void ADebug::LogError(const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    LogError(pszFormatToFString(pszFormat, args));
    va_end(args);
}

void ADebug::Assert(bool condition, FString message) {
    if (!condition) {
        message.InsertAt(0, "ASSERTION FAILED: ");
        LogError(message);
    }
}

void ADebug::Assert(bool condition, const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    Assert(condition, pszFormatToFString(pszFormat, args));
    va_end(args);
}