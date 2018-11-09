// Fill out your copyright notice in the Description page of Project Settings.

#include "VRAppSwitchFunctionLibrary.h"
#include "NLogger.h"

#define FILENAME_APP_NEXT "../../../vr_app_next.tmp" //This is because the office application is actually nested deep inside the cooked folder

static bool g_bDidMarkNextProgram = false;

void UVRAppSwitchFunctionLibrary::markNextProgramName(FString name) {
	//don't write the next program twice
	//sometimes our hit events happen multiple times
	if (g_bDidMarkNextProgram)
		return;


	//Convert FString to C string
	char buffer[512];
	const TCHAR* pwszName = name.Len() > 0 ? &name[0] : TEXT("");;
	mbstate_t state;
	wcsrtombs(buffer, &pwszName, 512, &state);


	FILE* pFile = fopen(FILENAME_APP_NEXT, "w");
	if (pFile) {
		g_bDidMarkNextProgram = true;
		fprintf(pFile, buffer);
		fclose(pFile);
	}
}

void UVRAppSwitchFunctionLibrary::exit() {
	if (!g_bDidMarkNextProgram)
		markNextProgramName("");

	//GIsRequestingExit
	FGenericPlatformMisc::RequestExit(false);
	//std::exit(0);
}
