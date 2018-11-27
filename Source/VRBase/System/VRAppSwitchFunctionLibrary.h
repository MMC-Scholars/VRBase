// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "System/predefs.h"
#include "VRAppSwitchFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API UVRAppSwitchFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "UVRAppSwitchFunctionLibrary")
	static void markNextProgramName(FString name);

	UFUNCTION(BlueprintCallable, Category = "UVRAppSwitchFunctionLibrary")
	static void exit();
	
	
};
