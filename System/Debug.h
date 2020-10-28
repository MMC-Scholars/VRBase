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
    int m_iBufferSize = 512;

public:
    ADebug();

    /// Logs a message to the console.
    UFUNCTION(BlueprintCallable)
    static void Log(FString message);
};
