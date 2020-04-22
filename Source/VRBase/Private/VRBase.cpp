// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VRBase.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define LOCTEXT_NAMESPACE "FVRBaseModule"

void FVRBaseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("VRBase")->GetBaseDir();

	
}

void FVRBaseModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVRBaseModule, VRBase)

/*
#if WITH_EDITOR
// implement as game module for hot reload
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, VRBase, "VRBase")
#else
// implement as plugin
IMPLEMENT_MODULE(FVRBaseModule, VRBase)
#endif
*/