#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "predefs.h"

#include "VRAppSwitchFunctionLibrary.generated.h"

UCLASS()
class VRBASE_API UVRAppSwitchFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category = "UVRAppSwitchFunctionLibrary")
    static void markNextProgramName(FString name);

    UFUNCTION(BlueprintCallable, Category = "UVRAppSwitchFunctionLibrary")
    static void exit();
};
