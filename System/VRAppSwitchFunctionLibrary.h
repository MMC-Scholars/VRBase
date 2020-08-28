/**
 * This software is under partial ownership by The Ohio State University,
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
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
