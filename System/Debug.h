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
};
