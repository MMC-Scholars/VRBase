#pragma once

//#include "CoreMinimal.h"
//#include "Engine.h"
//#include "EngineMinimal.h"

#include "FPawnInstruction.generated.h"

USTRUCT(BlueprintType)
struct FPawnInstruction {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Instruction")
    FText text;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Instruction Color")
    FColor color = FColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Hand")
    EControllerHand hand = EControllerHand::Right;

    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              DisplayName = "Change on Button Press")
    bool changeOnButtonPress = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Change Time")
    float timedChange = 5.0;

    FPawnInstruction() {}

    FPawnInstruction(FString string) { text = FText::FromString(string); }
};