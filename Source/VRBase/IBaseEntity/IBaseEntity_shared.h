//This file is used to declare UPROPERTY and UFUNCTION accessible
// variables and functions shared between all classes which
// derive from IBaseEntity
// as IBaseEntity itself cannot have UPROPERTY or UFUNCTION

//These includes do not serve any purpose compile-time, they only help
//with parsing during editing
#ifndef IBASEENTITY_H
#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "System/predefs.h"
#include "System/Globals.h"
#include "System/static_initialize.h"
#include "IBaseEntity_flags.h"
#include "GameFramework/Actor.h"
#include "System/EHandle.h"
#endif

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
SEntityInputRegistrationParams m_leftControllerInput;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
SEntityInputRegistrationParams m_leftControllerInput;