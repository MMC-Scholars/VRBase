// Debug is intended to be a drop-in replacement for Unity's Debug class, which
// contains a collection of static methods to ease debugging while developing a game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Debug.generated.h"

UCLASS()
class ADebug : public AActor {
    GENERATED_BODY()

private:
    static const int m_iBufferSize = 512;

    static FString pszFormatToFString(const char* pszFormat, va_list args);

public:
    ADebug();

    /// Logs a message to the console.
    /// Accepts FStrings, format strings, and const char*.
    UFUNCTION(BlueprintCallable)
    static void Log(FString message, FLinearColor color = FLinearColor::White,
                    float duration = 5.0f);
    static void Log(const char* pzsFormat, ...);

    /// Logs a warning message to the console.
    /// Uses the same message format(s) as Log().
    UFUNCTION(BlueprintCallable)
    static void LogWarning(FString      message,
                           FLinearColor color    = FLinearColor(1, 0.9, 0, 1),
                           float        duration = 5.0f);
    static void LogWarning(const char* pzsFormat, ...);

    /// Logs an error message to the console.
    /// Uses the same message format(s) as Log().
    UFUNCTION(BlueprintCallable)
    static void LogError(FString      message,
                           FLinearColor color    = FLinearColor(1, 0, 0, 1),
                           float        duration = 5.0f);
    static void LogError(const char* pzsFormat, ...);

    /// Assert a condition and logs an error message to the Unity console on failure.
    /// Uses the same message format(s) as Log().
    UFUNCTION(BlueprintCallable)
    static void Assert(bool condition, FString message);
    static void Assert(bool condition, const char* pzsFormat, ...);
};